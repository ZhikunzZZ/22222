package com.ml.news.fragment

import android.annotation.SuppressLint
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.SeekBar
import androidx.recyclerview.widget.LinearLayoutManager
import com.ml.news.adapter.NewsAdapter
import com.ml.news.appViewModel
import com.ml.news.base.BaseVmFragment
import com.ml.news.base.ext.getResIdForName
import com.ml.news.base.ext.setCornerImg
import com.ml.news.bean.NewsBean
import com.ml.news.databinding.FragmentNewsBinding
import com.ml.news.vm.MainViewModel


class NewsFragment : BaseVmFragment<MainViewModel, FragmentNewsBinding>() {
    private lateinit var newsAdapter: NewsAdapter
    private var currentTime: Long = 0
    private var totalTime: Long = 0

    override fun initView(savedInstanceState: Bundle?) {
        initAdapter()
        mViewBind.apply {             //The music player function is not implemented, just add a listener
            playImg.setOnClickListener {

            }
            backwardImg.setOnClickListener {
                if (currentTime < 15000) {
                } else {
                }
            }
            forwardImg.setOnClickListener {
                if (totalTime - currentTime < 15000) {
                } else {
                }
            }
        }

    }

    override fun createObserver() {
        super.createObserver()
        //Monitor news data changes
        mViewModel.news.observeInFragment(this, ::setNewsData)
        //Monitor all news classification changes, and re-acquire data if there is a change
        appViewModel.selectNewsBean.observeInFragment(this, ::setNewsData)

        //SeekBar
        mViewBind.seekBar.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {}
            override fun onStartTrackingTouch(seekBar: SeekBar) {}
            override fun onStopTrackingTouch(seekBar: SeekBar) {
            }
        })
    }

    /**
     * 设置数据
     * @param newsData MutableList<NewsBean>
     */
    private fun setNewsData(newsData: MutableList<NewsBean>) {
        newsAdapter.selectPosition = 0
        //Replace the category data above
        newsAdapter.submitList(newsData)
        // set image and text
        setData(
            "0",
            newsData[0].newsType,
            newsData[0].newsDescImg,
        )
    }

    override fun lazyLoadData() {
        //get news data
        mViewModel.getNews(0)
    }

    //initialize adapter
    @SuppressLint("SetTextI18n", "NotifyDataSetChanged")
    private fun initAdapter() {
        mViewBind.apply {
            typeList.layoutManager =
                LinearLayoutManager(requireActivity(), LinearLayoutManager.HORIZONTAL, false)
            newsAdapter = NewsAdapter()
            typeList.adapter = newsAdapter
        }
        //item click event, click to update the selected item
        newsAdapter.setOnItemClickListener { _, _, position ->
            if (newsAdapter.selectPosition != position) {
                newsAdapter.selectPosition = position
                newsAdapter.notifyDataSetChanged()
                mViewBind.apply {
                    newsAdapter.apply {
                        setData(
                            position.toString(),
                            items[position].newsType,
                            items[position].newsDescImg,
                        )
                        mViewBind.seekBar.progress = 0              //Update seekbar, although not yet implemented
                        mViewBind.currentTimeTxt.text = "00:00"
                        mViewBind.totalTimeTxt.text = "00:00"
                    }

                }
            }
        }
    }

    /**
     * set data
     * @param id String
     * @param newType String
     * @param newsDesc String
     * @param newsVoiceUrl String
     */
    @SuppressLint("SetTextI18n")
    private fun setData(id: String, newType: String, newsDesc: String) {
        mViewBind.apply {
            newsTitleTxt.text = "$newType News" //set news title
            requireActivity().setCornerImg(
                requireActivity().getResIdForName(newsDesc), newsDescImg
            )
        }
    }
}