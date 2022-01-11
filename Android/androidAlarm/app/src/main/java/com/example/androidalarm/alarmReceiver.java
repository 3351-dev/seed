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
import android.util.Log;
import android.widget.Toast;

import androidx.annotation.RequiresApi;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;

public class alarmReceiver extends BroadcastReceiver {
    public final String CHANNEL_ID = "default";
    public final int NOTIFICATION_ID = 1;
    SharedPreferences mPreferences;

    // minSdkVersion이 지정한 버전보다 낮을경우 바로 호출시에는 컴파일 발생
    // 조건문을 통한 분기 처리르 통해 호출해야 에러가 발생하지않음
    @SuppressLint("UnspecifiedImmutableFlag")
    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public void onReceive(Context context, Intent intent) {

        createNotificationChannel(context);

        Toast.makeText(context,"ring ring",Toast.LENGTH_SHORT).show();
        Log.d("Alarm Receiver", "ring ring");

        mPreferences = context.getSharedPreferences("alarm", Context.MODE_PRIVATE);

        // 인텐트를 선언하지 않고 그냥 받으면 된다
        String pos = String.valueOf(intent.getIntExtra("pos",0));
        String title = mPreferences.getString(pos,"");
        String contents = mPreferences.getString(pos+"contents","");

        //snooze, cancel Activity setting
        Intent MainIntent = new Intent(context, MainActivity.class);
        MainIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        PendingIntent MainPendingIntent;
        MainPendingIntent = PendingIntent.getActivity(context, 0, MainIntent, PendingIntent.FLAG_ONE_SHOT);

        Intent snoozeIntent = new Intent(context, SNZActivity.class);
        snoozeIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        snoozeIntent.putExtra("value","3351");
        PendingIntent SNZPendingIntent = PendingIntent.getActivity(context, 0, snoozeIntent, PendingIntent.FLAG_ONE_SHOT);

        Intent cancelIntent = new Intent(context, cancelActivity.class);
        cancelIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        PendingIntent cancelPendingIntent = PendingIntent.getActivity(context, 0, cancelIntent, PendingIntent.FLAG_ONE_SHOT);

        // Alarm Setting
        NotificationCompat.Builder builder = new NotificationCompat.Builder(context,CHANNEL_ID)
                .setSmallIcon(R.drawable.ic_launcher_background)
                .setContentTitle(title)
                .setContentText(contents)
                .setPriority(NotificationManagerCompat.IMPORTANCE_MAX)
                .setContentIntent(MainPendingIntent)
                .addAction(R.drawable.ic_launcher_background,"SNZ",SNZPendingIntent)
                .addAction(R.drawable.ic_launcher_background,"Cancel",cancelPendingIntent);

        NotificationManagerCompat notificationManagerCompat = NotificationManagerCompat.from(context);
        notificationManagerCompat.notify(NOTIFICATION_ID,builder.build());
    }

    private void createNotificationChannel(Context context){
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
            CharSequence name = "default";
            String description = "default";
            int importance = NotificationManager.IMPORTANCE_DEFAULT;

            // Create Channel
            NotificationChannel notificationChannel = new NotificationChannel(CHANNEL_ID, name, importance );
            notificationChannel.setDescription(description);

            // Create AlarmManager setting
            NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);

            // register Channel in AlarmManager
            notificationManager.createNotificationChannel(notificationChannel);

        }
    }


}