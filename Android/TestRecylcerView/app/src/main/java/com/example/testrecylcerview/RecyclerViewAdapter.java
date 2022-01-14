package com.example.testrecylcerview;

import android.annotation.SuppressLint;
import android.util.SparseBooleanArray;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.RecyclerViewAccessibilityDelegate;

import java.util.ArrayList;

public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

    private ArrayList<DataMovie> listData = new ArrayList<>();

    // Item 클릭 상태를 저장할 array 객체
    private SparseBooleanArray selectedItems = new SparseBooleanArray();
    // 직전에 클릭됐던 Item position
    private int prePosition = -1;

    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.itme_movie, parent, false);
        return new ViewHolderMovie(view);
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, @SuppressLint("RecyclerView") final int position) {
        ViewHolderMovie viewHolderMovie = (ViewHolderMovie) holder;
//        ((ViewHolderMovie)holder).onBind(listData.get(position));
        viewHolderMovie.onBind(listData.get(position),position,selectedItems);
        viewHolderMovie.setOnViewHolderItemClickListener(new OnViewHolderItemClickListener(){
            @Override
            public void onViewHolderItemClick() {
                if (selectedItems.get(position)) {
                    selectedItems.delete(position);
                }else{
                    selectedItems.delete(prePosition);
                    selectedItems.put(position, true);
                }
                if(prePosition != -1) notifyItemChanged(prePosition);
                notifyItemChanged(position);
                prePosition = position;
            }
        });
    }

    @Override
    public int getItemCount() {
        return listData.size();
    }

    void addItem(DataMovie data){
        listData.add(data);
    }
}
