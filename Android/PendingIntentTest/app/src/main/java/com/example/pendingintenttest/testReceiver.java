package com.example.pendingintenttest;

import android.annotation.SuppressLint;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.util.Log;

import androidx.annotation.RequiresApi;

public class testReceiver extends BroadcastReceiver {
    private final String TAG = this.getClass().getSimpleName();
    public final String CHANNEL_ID = "default";

    @SuppressLint("UnspecifiedImmutableFlag")
    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public void onReceive(Context context, Intent intent) {

        createNotificationChannel(context);

        String message = intent.getStringExtra("3351");
        Log.d(TAG,"it's snzReceiver here. "+message);
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
