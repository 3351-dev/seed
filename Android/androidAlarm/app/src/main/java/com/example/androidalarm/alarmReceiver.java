package com.example.androidalarm;

import android.annotation.SuppressLint;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Build;
import android.util.Log;
import android.widget.Toast;

import androidx.annotation.RequiresApi;
import androidx.core.app.NotificationCompat;

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

        // 채널 생성
//        NotificationCompat.Builder builder = new NotificationCompat.Builder(context, "default");
//        builder.addAction(R.drawable.ic_launcher_background,"notification Test",intent);

        // Icon, title, contents
        //builder.setSmallIcon(R.drawable.ic_launcher_background);
        // builder.setContentTitle(title);
        // builder.setContentText(contents);
        // builder.setAutoCancel(true);

        // Notification Test
        Intent snoozeIntent = new Intent(context,alarmReceiver.class);

        Intent cancel = new Intent(context, cancelActivity.class);
        cancel.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        @SuppressLint("UnspecifiedImmutableFlag")
        PendingIntent cancelPendingIntent = PendingIntent.getActivity(context,(int) (System.currentTimeMillis()/1000 ),cancel,PendingIntent.FLAG_ONE_SHOT);


        //snoozeIntent.setAction(ACTION_SNOOZE);
        // snoozeIntent.putExtra(EXTRA_NOTIFICATION_ID,0);

        // Todo
        /*
            * setContentIntent(~~~) : 실행할 작업 인텐트를 설정
            * setAutoCancel(true)   : 탭하면 자동으로 알림을 삭제
            *
            *
        */
        @SuppressLint("UnspecifiedImmutableFlag")
        PendingIntent snoozePendingIntent = PendingIntent.getBroadcast(context,0,snoozeIntent,0);
        NotificationCompat.Builder builder1 =
                new NotificationCompat.Builder(context,"default")
                .setSmallIcon(R.drawable.ic_launcher_background)
                .setContentTitle(title)
                .setContentText(contents)
                .setPriority(NotificationCompat.PRIORITY_MAX)
                .addAction(R.drawable.off_radius, "SNZ",snoozePendingIntent)
                .addAction(R.drawable.off_radius, "Cancel",cancelPendingIntent)
                .setAutoCancel(true)
                .setContentIntent(cancelPendingIntent)
                .setDefaults(Notification.DEFAULT_VIBRATE); // vibrate setting

        // 알림 매니저 생성
        NotificationManager notificationManager =
                (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        // 알림 매니저에 채널등록
        notificationManager.createNotificationChannel(new NotificationChannel("default","default",NotificationManager.IMPORTANCE_DEFAULT));

        // 알람의 고유한 id는 적당한 정수값을 넣어줌
        notificationManager.notify(1,builder1.build());
        // SNZ 클릭시 여러개의 알림 계속 생성(시간이 다 다르므로)
//        notificationManager.notify((int) (System.currentTimeMillis()/1000),builder1.build());


    }

}