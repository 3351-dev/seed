package com.example.recyclerviewtest;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.cardview.widget.CardView;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class recyclerAdapter extends RecyclerView.Adapter<recyclerAdapter.ViewHolder>{

    private final List<CardItem> mDateList;
    private RecyclerViewClickListener mListener;
    LinearLayout expandable_view;

    public recyclerAdapter(List<CardItem> dataList){
        mDateList = dataList;
    }

    public void setOnClickListener(RecyclerViewClickListener listener){
        mListener = listener;
    }

    public interface RecyclerViewClickListener{
//       아이템 클릭 처리
        void onItemClicked(int position);
        void onShareButtonClicked(int position);
        void onLearnMoreButtonClicked(int position);
    }


    @Override
    //    뷰 홀더를 생성하는 부분, 레이아웃을 만드는 부분
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.item_card, parent, false);

//        expandable_view = view.findViewById(R.id.expandable_view);
//        Log.d("3351 "," "+expandable_view.getVisibility());

        return new ViewHolder(view);
    }

    @Override
    //    뷰 홀더에 데이터를 설정하는 부분
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        CardItem item = mDateList.get(position);
        holder.title.setText(item.getTitle());
        holder.contents.setText(item.getContents());

        if(mListener != null){
            //현재 위치
            final int pos = position;
            holder.itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    expandable_view = view.findViewById(R.id.expandable_view);
                    mListener.onItemClicked(pos);
//                    Log.d("view","Item : "+ pos);
//                    Log.d("view","Item : "+ expandable_view.getVisibility());
                    if(expandable_view.getVisibility() == View.GONE){
                        expandable_view.setVisibility(View.VISIBLE);
                    }else{
                        expandable_view.setVisibility(View.GONE);
                    }
                }
            });
            holder.share.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    mListener.onShareButtonClicked(pos);
                }
            });
            holder.more.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    mListener.onLearnMoreButtonClicked(pos);
                }
            });

        }

    }

    @Override
    //  아이템의 수
    public int getItemCount() {
        return mDateList.size();
    }

//    각각의 이이템의 레퍼런스를 저장할 뷰 홀더 클래스
//    반드시 RecyclerView.ViewHolder를 상속해야함
    public static class ViewHolder extends RecyclerView.ViewHolder{
        TextView title;
        TextView contents;
        Button share;
        Button more;
        public ViewHolder(View itemView){
            super(itemView);
            title = (TextView) itemView.findViewById(R.id.title_text);
            contents = (TextView) itemView.findViewById(R.id.contents_text);
            share = (Button) itemView.findViewById(R.id.share_button);
            more = (Button) itemView.findViewById(R.id.more_button);

        }
    }
    //  애니메이션 추가
    public void removeItem(int position){
        mDateList.remove(position);
        notifyItemRemoved(position);
        notifyItemRangeChanged(position,mDateList.size());
    }
    public void addItem(int position, CardItem item){
        mDateList.add(position, item);
        notifyItemInserted(position);
        notifyItemRangeChanged(position, mDateList.size());
    }
}
