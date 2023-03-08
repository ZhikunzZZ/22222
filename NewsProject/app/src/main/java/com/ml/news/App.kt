package com.ml.news

import androidx.multidex.MultiDex
import com.ml.news.vm.AppViewModel
import com.tencent.mmkv.MMKV
import me.hgj.jetpackmvvm.base.BaseApp

//Application's global ViewModel, which stores some account information, basic configuration information, etc.
val appViewModel: AppViewModel by lazy { App.appViewModelInstance }

class App : BaseApp() {

    companion object {
        lateinit var instance: App
        lateinit var appViewModelInstance: AppViewModel
    }

    override fun onCreate() {
        super.onCreate()
        MMKV.initialize(this)
        instance = this
        appViewModelInstance = getAppViewModelProvider()[AppViewModel::class.java]
        MultiDex.install(this)
    }
}