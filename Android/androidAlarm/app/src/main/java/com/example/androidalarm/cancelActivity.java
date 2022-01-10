package com.example.androidalarm;

import android.app.NotificationManager;
import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

public class cancelActivity extends AppCompatActivity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.fragment_view_3);

        NotificationManager notificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);

        notificationManager.cancel(1);
    }

}
