package com.example.bookrecyclerbiewexam2;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class Adapter extends RecyclerView.Adapter<Adapter.ViewHolder>{
    private final String TAG = this.getClass().getSimpleName();
    private final List<CardItem> mDataList;
    private AdapterClickListener mListener;

    public void setOnClickListener(AdapterClickListener listener){
        mListener = listener;
    }
    public interface AdapterClickListener{
        void onItemClicked(int position);
        void onBtn1Clicked(int position);
        void onBtn2Clicked(int position);
    }

    public Adapter(List<CardItem> dataList){
        mDataList = dataList;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.item_card, parent, false);

        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        CardItem item = mDataList.get(position);
        holder.title.setText(item.getTitle());
        holder. contents.setText(item.getContents());

        if(mListener != null){
            final int pos = position;
            holder.itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Log.d(TAG, pos+" click");
                    mListener.onItemClicked(pos);

                }
            });
            holder.btn1.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Log.d(TAG, pos+" click");
                    mListener.onBtn1Clicked(pos);

                }
            });
            holder.btn2.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Log.d(TAG, pos+" click");
                    mListener.onBtn2Clicked(pos);

                }
            });

        }
    }

    @Override
    public int getItemCount() {
        return mDataList.size();
    }

    public static class ViewHolder extends RecyclerView.ViewHolder{
        private final String TAG = this.getClass().getSimpleName();

        TextView title;
        TextView contents;
        ImageButton fold;
        LinearLayout contentsPart;
        Button btn1;
        Button btn2;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            title = itemView.findViewById(R.id.title_text);
            contents = itemView.findViewById(R.id.contents_text);
            fold = itemView.findViewById(R.id.contents_fold);
            contentsPart = itemView.findViewById(R.id.contents_part);
            btn1 = itemView.findViewById(R.id.btn_1);
            btn2 = itemView.findViewById(R.id.btn_2);

            title.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Log.d(TAG,getAdapterPosition()+"  Title Click" );
                    contents.setText("<3");
                }
            });

            fold.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Log.d(TAG, getAdapterPosition()+" fold");
                    contentsPart.setVisibility(View.GONE);
                    fold.setImageResource(R.drawable.ic_baseline_keyboard_arrow_down_24);
                }
            });

        }

    }

    public void removeItem(int position){
        mDataList.remove(position);
        notifyItemRemoved(position);
        notifyItemRangeChanged(position, mDataList.size());
    }

    public void addItem(int position, CardItem item){
        mDataList.add(position, item);
        notifyItemInserted(position);
        notifyItemRangeChanged(position, mDataList.size());
    }
}
