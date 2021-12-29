package com.example.androidalarm;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
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
        recyclerAdapter recyclerAdapter = new recyclerAdapter(dataList);
        recyclerView.setLayoutManager(new LinearLayoutManager(getActivity()));
        recyclerView.setAdapter(recyclerAdapter);


        mAdapter = new recyclerAdapter(dataList);
        mAdapter.setOnClickListener(this);
        recyclerView.setAdapter(mAdapter);


        return rootView;
    }

    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

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
        mAdapter.addItem(position, new CardItem("Add","Add"));
    }

    public void onLearnMoreButtonClicked(int position) {
        Log.d(" ","More : " + position);
        mAdapter.removeItem(position);
    }



}
