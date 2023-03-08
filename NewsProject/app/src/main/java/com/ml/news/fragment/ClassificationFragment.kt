package com.ml.news.fragment

import android.os.Bundle
import android.util.Log
import android.widget.Toast
import androidx.recyclerview.widget.GridLayoutManager
import com.ml.news.adapter.ClassificationAdapter
import com.ml.news.appViewModel
import com.ml.news.base.BaseVmFragment
import com.ml.news.bean.NewsBean
import com.ml.news.databinding.FragmentClassificationBinding
import com.ml.news.vm.MainViewModel
import java.util.stream.Collectors

/**
 * Classification page
 */
class ClassificationFragment : BaseVmFragment<MainViewModel, FragmentClassificationBinding>() {
    private lateinit var classificationAdapter: ClassificationAdapter

    override fun initView(savedInstanceState: Bundle?) {
        initAdapter()
    }

    //lazy load data
    override fun lazyLoadData() {
        mViewModel.getNews(1)
    }

    override fun createObserver() {

        super.createObserver()
        //monitor local news data
        mViewModel.news.observeInFragment(this) {
            classificationAdapter.submitList(it)
        }
    }

    //initialize adapter
    private fun initAdapter() {
        mViewBind.apply {
            typeList.layoutManager = GridLayoutManager(requireActivity(), 3)
            classificationAdapter = ClassificationAdapter()
            typeList.adapter = classificationAdapter
        }

        classificationAdapter.apply {
            setOnItemClickListener { _, _, position ->
                // the number of selected news
                val count = this.items.stream().filter { newsBean -> newsBean.isSelect }.count()
                //Query whether it is the last selected category, if yes, prompt
                if (getItem(position)?.isSelect == true && count == 1L) {
                    Toast.makeText(requireActivity(), "at least choose one news", Toast.LENGTH_SHORT).show()
                } else {
                    // reverse selection
                    getItem(position)?.isSelect = getItem(position)?.isSelect != true
                    notifyItemChanged(position)
                    // selectTypes which is the array of selected news
                    val selectTypes: MutableList<NewsBean> =
                        classificationAdapter.items.stream()
                            .filter { newsBean -> newsBean.isSelect }
                            .collect(Collectors.toList())
                    //notify home page news data refresh
                    appViewModel.selectNewsBean.postValue(selectTypes)
                }
            }
        }
    }


}