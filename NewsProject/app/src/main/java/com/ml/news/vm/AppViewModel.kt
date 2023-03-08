package com.ml.news.vm

import com.ml.news.bean.NewsBean
import me.hgj.jetpackmvvm.base.viewmodel.BaseViewModel
import me.hgj.jetpackmvvm.callback.livedata.event.EventLiveData

class AppViewModel : BaseViewModel() {
    var selectNewsBean = EventLiveData<MutableList<NewsBean>>()
}