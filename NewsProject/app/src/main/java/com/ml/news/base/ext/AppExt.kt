package com.ml.news.base.ext

import android.content.Context
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.AppCompatImageView
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentTransaction
import com.bumptech.glide.Glide
import com.bumptech.glide.load.resource.bitmap.CenterCrop
import com.bumptech.glide.load.resource.bitmap.RoundedCorners
import com.bumptech.glide.request.RequestOptions
import me.hgj.jetpackmvvm.ext.util.dp2px

/**
 * add fragment in activity
 */
fun AppCompatActivity.add(layoutId: Int, fragment: Fragment) {
    supportFragmentManager.beginTransaction()
        .add(layoutId, fragment)
        .commitAllowingStateLoss()
}

/**
 * show and hide fragment
 */
fun AppCompatActivity.showHide(
    oldFragment: Fragment,
    hideFragment: Fragment,
) {
    val transaction = this.supportFragmentManager.beginTransaction()
    transaction.setTransition(FragmentTransaction.TRANSIT_FRAGMENT_FADE)            //set transaction
    transaction.hide(hideFragment)                                                  //hide
    transaction.show(oldFragment)                                                   //show
    transaction.commit()                                                            //commit
}

/**
 * set corner image
 */
fun Context.setCornerImg(url: Int?, imageView: AppCompatImageView) {
    Glide.with(this)
        .asBitmap()
        .load(url)
        .transform(CenterCrop(), RoundedCorners(dp2px(10)))
        .into(imageView)
}


/**
 * set corner image
 */
fun Context.setCornerImg(url: String?, imageView: AppCompatImageView) {
    Glide.with(this).asBitmap()
        .load(url)
        .apply(RequestOptions.bitmapTransform(RoundedCorners(dp2px(10))))
        .into(imageView)
}

/**
 * Get the resource file id according to the resource file name
 */
fun Context.getResIdForName(resName: String?): Int {
    return resources.getIdentifier(resName, "drawable", packageName)
}

