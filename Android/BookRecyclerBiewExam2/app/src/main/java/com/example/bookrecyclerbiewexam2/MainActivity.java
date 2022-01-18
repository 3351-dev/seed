package com.example.bookrecyclerbiewexam2;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements Adapter.AdapterClickListener{

    private final String TAG = this.getClass().getSimpleName();
    private Adapter mAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        RecyclerView recyclerView = (RecyclerView) findViewById(R.id.recycler_view);
        // LayoutManager
        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(this);
        recyclerView.setLayoutManager(layoutManager);
        // data
        List<CardItem> dataList = new ArrayList<>();
        for(int i=0;i<5;i++){
            dataList.add(new CardItem(""+i+"'s Item",""+i+"'s Contents"));
        }

        // Adapter Setting
        mAdapter = new Adapter(dataList);
            // ClickListener
        mAdapter.setOnClickListener(this);
        recyclerView.setAdapter(mAdapter);
    }

    @Override
    public void onItemClicked(int position) {
//        Log.d(TAG, position+" item clicked");
    }

    @Override
    public void onBtn1Clicked(int position) {
//        Log.d(TAG, position+" Btn 1 clicked");
        mAdapter.addItem(position, new CardItem("Add","Add"));
    }

    @Override
    public void onBtn2Clicked(int position) {
//        Log.d(TAG, position+ " Btn 2 clicked");
        mAdapter.removeItem(position);
    }
}