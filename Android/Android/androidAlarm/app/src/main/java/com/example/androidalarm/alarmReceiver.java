package com.example.androidalarm;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

public class alarmReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
        Toast.makeText(context,"ring ring",Toast.LENGTH_SHORT).show();
        Log.d("Alarm Receiver", "ring ring");
    }
}
