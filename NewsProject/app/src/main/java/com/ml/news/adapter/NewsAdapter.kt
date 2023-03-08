package com.ml.news.adapter

import android.content.Context
import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import com.chad.library.adapter.base.BaseQuickAdapter
import com.ml.news.R
import com.ml.news.base.ext.getResIdForName
import com.ml.news.base.ext.setCornerImg
import com.ml.news.bean.NewsBean
import com.ml.news.databinding.ItemNewsLayoutBinding

class NewsAdapter : BaseQuickAdapter<NewsBean, NewsAdapter.VH>() {
    var selectPosition: Int = 0

    class VH(
        parent: ViewGroup,
        val binding: ItemNewsLayoutBinding = ItemNewsLayoutBinding.inflate(
            LayoutInflater.from(parent.context), parent, false
        ),
    ) : RecyclerView.ViewHolder(binding.root)

    override fun onCreateViewHolder(context: Context, parent: ViewGroup, viewType: Int): VH {
        // return a ViewHolder
        return VH(parent)
    }

    override fun onBindViewHolder(holder: VH, position: Int, item: NewsBean?) {
        if (selectPosition == position) {
            holder.binding.itemLayout.setBackgroundResource(R.drawable.shape_type_select)
        } else {
            holder.binding.itemLayout.setBackgroundResource(R.drawable.shape_type_unselect)
        }
        context.setCornerImg(context.getResIdForName(item?.newsIcon), holder.binding.newsImg)
        holder.binding.newsNameTxt.text = item?.newsType
    }

}