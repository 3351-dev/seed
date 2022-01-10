package com.example.androidalarm;

import android.app.NotificationManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.util.Log;
import android.widget.Toast;

import androidx.core.app.NotificationCompat;
import androidx.fragment.app.Fragment;

public class alarmReceiver extends BroadcastReceiver{
    Context context;
    SharedPreferences mPreferences;
    SharedPreferences.Editor editor = mPreferences.edit();

    @Override
    public void onReceive(Context context, Intent intent) {
        Toast.makeText(context,"ring ring",Toast.LENGTH_SHORT).show();
        Log.d("Alarm Receiver", "ring ring");

        // 인텐트를 선언하지 않고 그냥 받으면 된다
        String contents = intent.getStringExtra("pos");
        NotificationCompat.Builder builder = new NotificationCompat.Builder(context, "default");
        builder.setSmallIcon(R.mipmap.ic_launcher);
        builder.setContentTitle("Ring Ring");
        builder.setContentText(contents);

        NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        notificationManager.notify(1,builder.build());

    }

}
