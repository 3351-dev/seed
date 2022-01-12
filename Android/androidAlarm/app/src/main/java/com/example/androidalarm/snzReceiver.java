package com.example.androidalarm;

import android.annotation.SuppressLint;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Build;
import android.util.Log;
import android.view.ViewGroup;

import java.util.prefs.Preferences;

public class snzReceiver extends BroadcastReceiver {
    private final String TAG = this.getClass().getSimpleName();
    public final String CHANNEL_ID = "default";
    public final int NOTIFICATION_ID = 1;
    SharedPreferences mPreferences;
    Context mContext;

    @SuppressLint("ResourceType")
    @Override
    public void onReceive(Context context, Intent intent) {
        // channel
        createNotificationChannel(context);
        // preferences
        mPreferences = context.getSharedPreferences("alarm",Context.MODE_PRIVATE);
        SharedPreferences.Editor editor= mPreferences.edit();

        String pos = intent.getStringExtra("pos");
        Log.d(TAG,"it's snzReceiver here. "+pos);

        editor.putString(pos+"onOff","off");
        editor.apply();

        NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        notificationManager.cancel(1);

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
