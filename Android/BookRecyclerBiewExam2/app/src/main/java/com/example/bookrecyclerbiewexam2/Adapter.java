package com.example.bookrecyclerbiewexam2;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class Adapter extends RecyclerView.Adapter<Adapter.ViewHolder>{
    private final String TAG = this.getClass().getSimpleName();
    private final List<CardItem> mDataList;
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
        holder.contents.setText(item.getContents());
    }

    @Override
    public int getItemCount() {
        return mDataList.size();
    }

    public static class ViewHolder extends RecyclerView.ViewHolder{
        private final String TAG = this.getClass().getSimpleName();
        TextView title;
        TextView contents;
        TextView fold;
        LinearLayout contentsPart;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            title = itemView.findViewById(R.id.title_text);
            contents = itemView.findViewById(R.id.contents_text);
            fold = itemView.findViewById(R.id.contents_fold);
            contentsPart = itemView.findViewById(R.id.contents_part);

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
                    contentsPart.src
                }
            });
        }
    }
}
