package com.ml.news.util

import android.text.TextUtils
import com.google.gson.Gson
import com.google.gson.JsonParser
import com.google.gson.reflect.TypeToken
import com.ml.news.bean.NewsBean
import com.tencent.mmkv.MMKV
import me.hgj.jetpackmvvm.base.appContext
import java.io.BufferedReader
import java.io.IOException
import java.io.InputStream
import java.io.InputStreamReader
import java.lang.reflect.Type


object Util {
    /**
     * Get user classification information
     */
    fun getNews(): MutableList<NewsBean>? {
        val kv = MMKV.defaultMMKV()
        val newsStr = kv.decodeString("newsIds")
        val type: TypeToken<List<NewsBean>> = object : TypeToken<List<NewsBean>>() {}
        val typeOfT: Type = type.type
        return if (TextUtils.isEmpty(newsStr)) {
            null
        } else {
            Gson().fromJson(newsStr, typeOfT)
        }
    }

    /**
     * Save the classification selected by the user
     */
    fun setNews(news: List<NewsBean>) {
        val kv = MMKV.defaultMMKV()
        kv.encode("newsIds", Gson().toJson(news))
    }

    fun <T> getList(json: String?, cls: Class<T>?): MutableList<T> {
        // Json data
        val newStringBuilder = StringBuilder()
        var inputStream: InputStream? = null
        try {
            inputStream = appContext.resources.assets.open(json!!)
            val isr = InputStreamReader(inputStream)
            val reader = BufferedReader(isr)
            var jsonLine: String?
            while (reader.readLine().also { jsonLine = it } != null) {
                newStringBuilder.append(jsonLine)
            }
            reader.close()
            isr.close()
            inputStream.close()
        } catch (e: IOException) {
            e.printStackTrace()
        }
        val str = newStringBuilder.toString()
        val list: MutableList<T> = ArrayList()
        val jsonArray = JsonParser().parse(str).asJsonArray
        val gson = Gson()
        for (jsonElement in jsonArray) {
            list.add(gson.fromJson(jsonElement, cls))
        }
        return list
    }

}