package com.example.androidalarm;

import android.annotation.SuppressLint;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import androidx.annotation.RequiresApi;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;

public class alarmReceiver extends BroadcastReceiver {
    public final String CHANNEL_ID = "default";
    public final int NOTIFICATION_ID = 1;
    private final String TAG = this.getClass().getSimpleName();
    SharedPreferences mPreferences;

    // minSdkVersion 이 지정한 버전보다 낮을경우 바로 호출시에는 컴파일 발생
    // 조건문을 통한 분기 처리르 통해 호출해야 에러가 발생하지않음
    @SuppressLint("UnspecifiedImmutableFlag")
    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public void onReceive(Context context, Intent intent) {

        createNotificationChannel(context);

        Toast.makeText(context,"ring ring",Toast.LENGTH_SHORT).show();
        Log.d(TAG, "ring ring");

        mPreferences = context.getSharedPreferences("alarm", Context.MODE_PRIVATE);

        // 인텐트를 선언하지 않고 그냥 받으면 된다
        String pos = String.valueOf(intent.getIntExtra("pos",999));
        String title = mPreferences.getString(pos,"");
        String contents = mPreferences.getString(pos+"contents","");

        //snooze, cancel Activity setting
        // 아무 동작하지 않는다면 getActivity, getService, getBroadcast 확인할 것
            // Main (확인용)
        Intent MainIntent = new Intent(context, MainActivity.class);
        MainIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        PendingIntent MainPendingIntent
                = PendingIntent.getActivity(context, 0
                , MainIntent, PendingIntent.FLAG_ONE_SHOT);

            // snooze
//        Intent snoozeIntent = new Intent(context, SNZActivity.class);
        Intent snoozeIntent = new Intent(context, snzReceiver.class);
        snoozeIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        snoozeIntent.putExtra("pos",pos);
        PendingIntent SNZPendingIntent
                = PendingIntent.getBroadcast(context, Integer.parseInt(pos)
                , snoozeIntent, PendingIntent.FLAG_UPDATE_CURRENT);

            // cancel
        Intent cancelIntent = new Intent(context, cancelActivity.class);
//        cancelIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        PendingIntent cancelPendingIntent
                = PendingIntent.getActivity(context, 0
                ,cancelIntent, PendingIntent.FLAG_ONE_SHOT);

        // Alarm Setting
        NotificationCompat.Builder builder = new NotificationCompat.Builder(context,CHANNEL_ID)
                .setSmallIcon(R.drawable.ic_baseline_alarm_24)
                .setContentTitle(title)
                .setContentText(contents)
                .setPriority(NotificationManagerCompat.IMPORTANCE_MAX)
                .setContentIntent(MainPendingIntent)
                .setAutoCancel(true)
                .addAction(R.mipmap.ic_launcher,"dismiss",SNZPendingIntent)
//                .addAction(R.drawable.ic_launcher_background,"Cancel",cancelPendingIntent)
                ;

        NotificationManagerCompat notificationManagerCompat = NotificationManagerCompat.from(context);
        notificationManagerCompat.notify(Integer.parseInt(pos),builder.build());
    }

    private void createNotificationChannel(Context context){
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
            CharSequence name = "default";
            String description = "default";
            int importance = NotificationManager.IMPORTANCE_DEFAULT;

            // Create Channel
            NotificationChannel notificationChannel = new NotificationChannel (CHANNEL_ID, name, importance );
            notificationChannel.setDescription(description);

            // Create AlarmManager setting
            NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);

            // register Channel in AlarmManager
            notificationManager.createNotificationChannel(notificationChannel);

        }
    }

}