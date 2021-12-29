package com.example.recyclerviewtest;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

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
        dataList.add(new CardItem("Third Item", "one\ntwo\nthree"));

        recyclerAdapter adapter = new recyclerAdapter(dataList);
        recyclerView.setAdapter(adapter);
    }
}