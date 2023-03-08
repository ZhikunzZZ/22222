package com.ml.news

import android.os.Bundle
import android.util.Log
import android.view.View
import com.ml.news.base.BaseVmActivity
import com.ml.news.base.ext.add
import com.ml.news.base.ext.showHide
import com.ml.news.databinding.ActivityMainBinding
import com.ml.news.fragment.ClassificationFragment
import com.ml.news.fragment.NewsFragment
import com.ml.news.util.Util
import com.ml.news.vm.MainViewModel


/**
 * Main activity
 */
class MainActivity : BaseVmActivity<MainViewModel, ActivityMainBinding>() {
    //news page
    private var newsFragment = NewsFragment()

    //classification page
    private var classificationFragment = ClassificationFragment()

    //local page
    private var currentPager = 0

    override fun initView(savedInstanceState: Bundle?) {
        //add news and classification fragment to activity
        add(R.id.fragment_lay, newsFragment)
        add(R.id.fragment_lay, classificationFragment)

        //Show news page by default
        showHide(newsFragment, classificationFragment)

        mViewBind.apply {
            newsTab.setOnClickListener { //bottom news button click
                if (currentPager != 0) {  //if already at news page, not thing happen. else, change the page
                    showHide(newsFragment, classificationFragment)
                    currentPager = 0
                    setTabStatus()
                }
            }
            classificationTab.setOnClickListener {////bottom classification button click
                if (currentPager != 1) {  //same with news button
                    showHide(classificationFragment, newsFragment)
                    currentPager = 1
                    setTabStatus()
                }
            }
        }
    }

    override fun createObserver() {
        super.createObserver()

        appViewModel.selectNewsBean.observeInActivity(this) {
            //Update local cache data
            Util.setNews(it)
        }
    }

    /**
     * Set the image and text of the two bottom button.
     */
    private fun setTabStatus() {
        mViewBind.apply {
            newsTxtLay.visibility = if (currentPager == 0) View.VISIBLE else View.GONE
            newsImg.visibility = if (currentPager == 0) View.GONE else View.VISIBLE
            classificationImg.visibility = if (currentPager == 1) View.GONE else View.VISIBLE
            classificationTxtLay.visibility = if (currentPager == 1) View.VISIBLE else View.GONE
        }
    }

}