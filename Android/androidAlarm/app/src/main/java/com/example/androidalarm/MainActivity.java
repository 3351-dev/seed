package com.example.androidalarm;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.tabs.TabLayout;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class MainActivity extends FragmentActivity {
    private final String TAG = this.getClass().getSimpleName();
    TabLayout tabs;

    fragment_view_1 fragment1;
    fragment_view_2 fragment2;
    fragment_view_3 fragment3;
    fragment_view_4 fragment4;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.init();
        registerReceiver(broadcastReceiver, new IntentFilter("snz"));

    }

    void init(){
        // hide actionBar
/*        ActionBar actionBar = getSupportActionBar();
        assert actionBar!= null;
        actionBar.hide();*/

        fragment1 = new fragment_view_1();
        fragment2 = new fragment_view_2();
        fragment3 = new fragment_view_3();
        fragment4 = new fragment_view_4();

        getSupportFragmentManager().beginTransaction().add(R.id.container, fragment1).commit();

        tabs = findViewById(R.id.tabs);
        tabs.addTab(tabs.newTab().setText("Alarm"));
        tabs.addTab(tabs.newTab().setText("Clock"));
        tabs.addTab(tabs.newTab().setText("Timer"));
        tabs.addTab(tabs.newTab().setText("Stop watch"));

        tabs.setOnTabSelectedListener(new TabLayout.OnTabSelectedListener() {
            @Override
            public void onTabSelected(TabLayout.Tab tab){
                int position = tab.getPosition();
                Fragment selected = null;
                if(position==0)
                    selected = fragment1;
                if(position==1)
                    selected = fragment2;
                if(position==2)
                    selected = fragment3;
                if(position==3)
                    selected = fragment4;

                getSupportFragmentManager().beginTransaction().replace(R.id.container, selected).commit();
            }

            @Override
            public void onTabUnselected(TabLayout.Tab tab){
            }

            @Override
            public void onTabReselected(TabLayout.Tab tab){
            }

        });


    }

    BroadcastReceiver broadcastReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {

            fragment_view_1 tf = (fragment_view_1) getSupportFragmentManager().findFragmentById(R.id.container);
            tf.getRefresh();


            Log.d(TAG, "snz call");
        }
    };

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(broadcastReceiver);
    }
}