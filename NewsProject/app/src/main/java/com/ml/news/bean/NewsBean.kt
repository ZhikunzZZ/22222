package com.ml.news.bean

/**
 * News entity class
 * newsType
 * newsIcon
 * newsDescImg
 */
data class NewsBean(
    var id: Int,
    var newsType: String,
    var newsIcon: String,
    var newsDescImg: String,
    var isSelect: Boolean,
)