package com.example.androidalarm;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Build;
import android.util.Log;
import android.widget.Toast;

import androidx.annotation.RequiresApi;
import androidx.core.app.NotificationCompat;
import androidx.fragment.app.Fragment;

public class alarmReceiver extends BroadcastReceiver{

    SharedPreferences mPreferences;

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public void onReceive(Context context, Intent intent) {
        Toast.makeText(context,"ring ring",Toast.LENGTH_SHORT).show();
        Log.d("Alarm Receiver", "ring ring");

        mPreferences = context.getSharedPreferences("alarm", Context.MODE_PRIVATE);

        // 인텐트를 선언하지 않고 그냥 받으면 된다
        String pos = String.valueOf(intent.getIntExtra("pos",0));
        String title = mPreferences.getString(pos,"");
        String contents = mPreferences.getString(pos+"contents","");

        NotificationCompat.Builder builder = new NotificationCompat.Builder(context, "default");
        builder.setSmallIcon(R.drawable.ic_launcher_background);

        builder.setContentTitle(title);
        builder.setContentText(contents);

        NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        notificationManager.createNotificationChannel(new NotificationChannel("default","default",NotificationManager.IMPORTANCE_DEFAULT));

        notificationManager.notify(1,builder.build());

    }

}
