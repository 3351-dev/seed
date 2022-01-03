package com.example.androidalarm;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.LinearLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.RecyclerViewAccessibilityDelegate;

import java.util.ArrayList;
import java.util.List;

public class fragment_view_1 extends Fragment implements recyclerAdapter.RecyclerViewClickListener{

    private RecyclerView recyclerView;
    private List<CardItem> dataList;
    private recyclerAdapter mAdapter;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @NonNull ViewGroup container,
                             @NonNull Bundle savedInstanceState){
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_view_1, container, false);

        recyclerView = rootView.findViewById(R.id.connect_recyclerview);
        // RecyclerView Adapter
        recyclerAdapter recyclerAdapter = new recyclerAdapter(dataList,getContext());
        recyclerView.setLayoutManager(new LinearLayoutManager(getActivity()));
        recyclerView.setAdapter(recyclerAdapter);


        mAdapter = new recyclerAdapter(dataList,getContext());
        mAdapter.setOnClickListener(this);
        recyclerView.setAdapter(mAdapter);


        return rootView;
    }

    // 어댑터 설정
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // 표시할 데이터
        dataList = new ArrayList<>();
        dataList.add(new CardItem("First","Android Boy"));
        dataList.add(new CardItem("Second","one\nTwo"));
        dataList.add(new CardItem("Third","1\n2\n3"));

    }

    public void onItemClicked(int position){
        Log.d(" ","Item : "+position);
    }

    public void onShareButtonClicked(int position){
        Log.d(" ", "share : "+position);
        //Item Add
        mAdapter.addItem(position+1, new CardItem("Add","Add"+position));
    }

    public void onDeleteButtonClicked(int position) {
        Log.d(" ","delete : " + position);
        mAdapter.removeItem(position);
    }

    @Override
    public void onRepeatCheckboxClicked(int position) {
        Log.d(" ","Item : "+position+10);
    }

}
