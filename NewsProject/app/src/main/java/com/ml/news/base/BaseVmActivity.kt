package com.ml.news.base

import android.os.Bundle
import androidx.viewbinding.ViewBinding
import me.hgj.jetpackmvvm.base.activity.BaseVmVbActivity
import me.hgj.jetpackmvvm.base.viewmodel.BaseViewModel

/**
 * Activity base class
 */
abstract class BaseVmActivity<VM : BaseViewModel, VB : ViewBinding> : BaseVmVbActivity<VM, VB>() {

    abstract override fun initView(savedInstanceState: Bundle?)

    /**
     * create LiveData observer
     */
    override fun createObserver() {}

    /**
     * open loading box
     */
    override fun showLoading(message: String) {
    }

    /**
     * close loading box
     */
    override fun dismissLoading() {
    }

}