package com.ml.news.vm

import com.ml.news.bean.NewsBean
import com.ml.news.util.Util
import me.hgj.jetpackmvvm.base.viewmodel.BaseViewModel
import me.hgj.jetpackmvvm.callback.livedata.event.EventLiveData

/**
 * 主页ViewModel，负责各种数据处理
 */
class MainViewModel : BaseViewModel() {
    var news: EventLiveData<MutableList<NewsBean>> = EventLiveData()


    //获取新闻内容  from 0 来自首页  1 来自分类页面
    fun getNews(from: Int) {
        val localNews = Util.getNews()
        val allNews = Util.getList("News.json", NewsBean::class.java)
        when (from) {
            0 -> {
                //如果数据没有用户选择的新闻分类那么就从json文件获取
                if (localNews.isNullOrEmpty()) {
                    allNews[0].isSelect = true
                    news.value = allNews
                } else {
                    localNews.forEach { localNew ->
                        allNews.forEach { allNew ->
                            if (localNew.id == allNew.id) {
                                localNew.newsType = allNew.newsType
                                localNew.newsDescImg = allNew.newsDescImg
                                localNew.newsIcon = allNew.newsIcon
                            }
                        }
                    }
                    //默认选中第一条
                    localNews[0].isSelect = true
                    news.value = localNews
                }

            }
            1 -> {
                if (localNews.isNullOrEmpty()) {
                    Util.setNews(allNews)
                    allNews.forEach { it.isSelect = true }
                } else {
                    localNews.forEach { localNew ->
                        allNews.forEach { allNew ->
                            if (localNew.id == allNew.id) {
                                allNew.isSelect = true
                            }
                        }
                    }
                }
                news.value = allNews
            }
        }
    }
}