package com.ml.news.base

import android.os.Bundle
import androidx.viewbinding.ViewBinding
import me.hgj.jetpackmvvm.base.fragment.BaseVmVbFragment
import me.hgj.jetpackmvvm.base.viewmodel.BaseViewModel

/**
 * Description: Fragment base class
 */
abstract class BaseVmFragment<VM : BaseViewModel, VB : ViewBinding> : BaseVmVbFragment<VM, VB>() {
    abstract override fun initView(savedInstanceState: Bundle?)


    /**
     * Create LiveData observer,triggered after Fragment executes onViewCreated
     */
    override fun createObserver() {}

    /**
     * Triggered after Fragment executes onViewCreated
     */
    override fun initData() {

    }

    /**
     * Open loading box
     */
    override fun showLoading(message: String) {
    }

    /**
     * Cloase loading box
     */
    override fun dismissLoading() {
    }

    /**
     * Lazy loading prevents the data from being loaded before the switching animation is completed, and the page will be rendered stuck at this time
     * animation is completed, and the page will be rendered stuck at this time
     * default 300ms
     * @return Long
     */
    override fun lazyLoadTime(): Long {
        return 300
    }
}