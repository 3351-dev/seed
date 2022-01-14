package com.example.testrecylcerview;

import android.animation.ValueAnimator;
import android.util.SparseBooleanArray;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

public class ViewHolderMovie extends RecyclerView.ViewHolder {
    TextView tv_movie_title;
    ImageView iv_movie, iv_movie2;
    LinearLayout linearLayout;

    OnViewHolderItemClickListener onViewHolderItemClickListener;

    public ViewHolderMovie(View view) {
        super(view);

        iv_movie = view.findViewById(R.id.iv_movie);
        tv_movie_title = view.findViewById(R.id.tv_movie_title);
        iv_movie2 = view.findViewById(R.id.iv_movie2);
        linearLayout = view.findViewById(R.id.linearlayout);

        linearLayout.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View view) {
                onViewHolderItemClickListener.onViewHolderItemClick();
            }
        });

    }

    public void onBind(DataMovie data, int position, SparseBooleanArray selectedItems){
        tv_movie_title.setText(data.getTitle());
        iv_movie.setImageResource(data.getImage());
        iv_movie2.setImageResource(data.getImage());
        changeVisibility(selectedItems.get(position));
    }

    private void changeVisibility(final boolean isExpanded){
        ValueAnimator va = isExpanded ? ValueAnimator.ofInt(0,600) : ValueAnimator.ofInt(600,0);
        va.setDuration(500);
        va.addUpdateListener(new ValueAnimator.AnimatorUpdateListener() {
            @Override
            public void onAnimationUpdate(ValueAnimator valueAnimator) {
                iv_movie2.getLayoutParams().height = (int) valueAnimator.getAnimatedValue();
                iv_movie2.requestLayout();
                iv_movie2.setVisibility(isExpanded? View.VISIBLE : View.GONE);
            }
        });
        va.start();
    }

    public void setOnViewHolderItemClickListener(OnViewHolderItemClickListener onViewHolderItemClickListener){
        this.onViewHolderItemClickListener = onViewHolderItemClickListener;
    }
}
