package com.example.recyclerviewtest;

import androidx.appcompat.app.AppCompatActivity;
import androidx.cardview.widget.CardView;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.transition.AutoTransition;
import android.transition.TransitionManager;
import android.util.Log;
import android.view.View;
import android.widget.LinearLayout;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements recyclerAdapter.RecyclerViewClickListener{

    private static final String TAG = MainActivity.class.getSimpleName();
    private recyclerAdapter mAdapter;
    LinearLayout expandable_view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        RecyclerView recyclerView = (RecyclerView) findViewById(R.id.recycler_view);
        // 레이아웃매니저로 LinearLayoutManger를 변경
        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(this);
        recyclerView.setLayoutManager(layoutManager);

        //표시할 데이터
        List<CardItem> dataList = new ArrayList<>();
        dataList.add(new CardItem("First Item","Android Boy"));
        dataList.add(new CardItem("Second Item", "one\ntwo"));
//        dataList.add(new CardItem("Third Item", "one\ntwo\nthree"));

        recyclerAdapter adapter = new recyclerAdapter(dataList);
        recyclerView.setAdapter(adapter);

        //어댑터 설정
//        recyclerAdapter adapter = new recyclerAdapter(dataList);
        adapter.setOnClickListener(this);
        recyclerView.setAdapter(adapter);

        mAdapter = new recyclerAdapter(dataList);
        mAdapter.setOnClickListener(this);
        recyclerView.setAdapter(mAdapter);

        // Expand View
        expandable_view = findViewById(R.id.expandable_view);

    }

    @Override
    public void onItemClicked(int position){
        Log.d(TAG,"Item : "+position);
    }

    @Override
    public void onShareButtonClicked(int position){
        Log.d(TAG, "share : "+position);
        //Item Add
        mAdapter.addItem(position, new CardItem("Add","Add"));
    }

    @Override
    public void onLearnMoreButtonClicked(int position) {
        Log.d(TAG,"More : " + position);
        mAdapter.removeItem(position);
    }

}