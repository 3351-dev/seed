package com.example.alarm2;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Build;
import android.widget.Toast;

import androidx.annotation.RequiresApi;
import androidx.core.app.NotificationCompat;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

public class AlarmReceiver extends BroadcastReceiver {

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public void onReceive(Context context, Intent intent){
        NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        Intent notificationIntent = new Intent(context, MainActivity.class);

        notificationIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP|Intent.FLAG_ACTIVITY_SINGLE_TOP);

        PendingIntent pendingI = PendingIntent.getActivity(context,0,notificationIntent,0);
        NotificationCompat.Builder builder=new NotificationCompat.Builder(context,"defualt");

        if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.O) {
            builder.setSmallIcon(R.drawable.ic_launcher_foreground);


            String channelName = "매일 알람 채널";
            String description = "매일 정해진 시간에 알람합니다";
            int importance = NotificationManager.IMPORTANCE_HIGH;

            NotificationChannel channel = new NotificationChannel("defualt", channelName, importance);
            channel.setDescription(description);

            if (notificationManager != null) {
                notificationManager.createNotificationChannel(channel);
            }
        }else{
            builder.setSmallIcon(R.mipmap.ic_launcher);
        }

        builder.setAutoCancel(true)
                .setDefaults(NotificationCompat.DEFAULT_ALL)
                .setWhen(System.currentTimeMillis())
                .setTicker("{Time to watch some cool stuff!!")
                .setContentTitle("Drag Title")
                .setContentText("Drag Sub title")
                .setContentInfo("Info")
                .setContentIntent(pendingI);
        if(notificationManager!=null){
            notificationManager.notify(1234,builder.build());
            Calendar nextNotifyTime = Calendar.getInstance();
            nextNotifyTime.add(Calendar.DATE,1);

            SharedPreferences.Editor editor = context.getSharedPreferences("daily alaram",Context.MODE_PRIVATE).edit();
            editor.putLong("nextNotifyTime",nextNotifyTime.getTimeInMillis());
            editor.apply();

            Date currentDateTime = nextNotifyTime.getTime();
            String date_text = new SimpleDateFormat("yyyy MM dd EE a hh mm ", Locale.getDefault()).format(currentDateTime);
            Toast.makeText(context.getApplicationContext(),"Next alarm is "+date_text,Toast.LENGTH_SHORT).show();

        }
    }
}
