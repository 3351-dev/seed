package com.example.androidalarm;

import android.app.NotificationManager;
import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

public class SNZActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
//        setContentView(R.layout.fragment_view_1);

        String extraData ="";
        Bundle extras = getIntent().getExtras();
        if(extras==null){
            extraData = "error";
        }else{
            extraData = extras.getString("value");
        }
        Log.d("snooze",""+extraData);

        NotificationManager notificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);

        Log.d("snooze","1111");

        notificationManager.cancel(1);
    }
}
