package com.example.recyclerviewtest;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.cardview.widget.CardView;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class recyclerAdapter extends RecyclerView.Adapter<recyclerAdapter.ViewHolder>{

    private final List<CardItem> mDateList;
    public recyclerAdapter(List<CardItem> dataList){
        mDateList = dataList;
    }


    @Override
    //    뷰 홀더를 생성하는 부분, 레이아웃을 만드는 부분
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.item_card, parent, false);

        return new ViewHolder(view);
    }

    @Override
    //    뷰 홀더에 데이터를 설정하는 부분
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        CardItem item = mDateList.get(position);
        holder.title.setText(item.getTitle());
        holder.contents.setText(item.getContents());

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
        public ViewHolder(View itemView){
            super(itemView);
            title = (TextView) itemView.findViewById(R.id.title_text);
            contents = (TextView) itemView.findViewById(R.id.contents_text);

        }
    }
}
