package com.example.androidalarm;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class recyclerAdapter extends RecyclerView.Adapter<recyclerAdapter.ViewHolder> {


    private final List<CardItem> mDataList;
    private RecyclerViewClickListener mListener;
    LinearLayout expandable_view;


    public recyclerAdapter(List<CardItem> DataList) {
        this.mDataList = DataList;
    }

    // Click Listener
    public void setOnClickListener(RecyclerViewClickListener listener){
        mListener = listener;
    }

    public interface RecyclerViewClickListener{
        void onItemClicked(int position);
        void onShareButtonClicked(int position);
        void onLearnMoreButtonClicked(int position);
    }



    @Override
    // 생성
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.item_card, parent, false);

        return new ViewHolder(view);
    }

    @Override
    // 데이터 설정
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        CardItem item = mDataList.get(position);
        holder.title.setText(item.getTitle());
        holder.contents.setText(item.getContents());

        if(mListener != null){
            final int pos = position;
            holder.itemView.setOnClickListener(new View.OnClickListener(){

                @Override
                public void onClick(View view) {
                    expandable_view = view.findViewById(R.id.expandable_view);
                    mListener.onItemClicked(pos);
                    if(expandable_view.getVisibility() == View.GONE){
                        expandable_view.setVisibility(View.VISIBLE);
                    }else{
                        expandable_view.setVisibility(View.GONE);
                    }
                }
            });
            holder.share.setOnClickListener(new View.OnClickListener(){

                @Override
                public void onClick(View view) {
                    mListener.onShareButtonClicked(pos);
                }
            });

            holder.more.setOnClickListener(new View.OnClickListener(){

                @Override
                public void onClick(View view) {
                    mListener.onLearnMoreButtonClicked(pos);
                }
            });

        }

    }

    @Override
    // 아이템 갯수
    public int getItemCount() {
        return mDataList.size();
    }

    public static class ViewHolder extends RecyclerView.ViewHolder{
        Button more;
        Button share;
        TextView title;
        TextView contents;

        public ViewHolder(View itemView) {
            super(itemView);
            title = (TextView) itemView.findViewById(R.id.title_text);
            contents = (TextView) itemView.findViewById(R.id.contents_text);
            more = (Button) itemView.findViewById(R.id.more_button);
            share = (Button) itemView.findViewById(R.id.share_button);

        }
    }
    //  애니메이션 추가
    public void removeItem(int position){
        mDataList.remove(position);
        notifyItemRemoved(position);
        notifyItemRangeChanged(position,mDataList.size());
    }
    public void addItem(int position, CardItem item){
        mDataList.add(position, item);
        notifyItemInserted(position);
        notifyItemRangeChanged(position, mDataList.size());
    }
}
