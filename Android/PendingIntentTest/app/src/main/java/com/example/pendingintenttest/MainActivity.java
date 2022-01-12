package com.example.pendingintenttest;

import android.annotation.SuppressLint;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.NotificationCompat;

@SuppressLint("UnspecifiedImmutableFlag")
@RequiresApi(api = Build.VERSION_CODES.O)
public class MainActivity extends AppCompatActivity {
    public final String CHANNEL_ID = "1";
    Button button = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button = (Button) findViewById(R.id.button);
        button.setOnClickListener(view -> NotificationSomethings());
    }

    private void NotificationSomethings() {
        int notification_id = 3351;
        Log.d("Main","Hello");
            // channel
        createNotificationChannel();
        // PendingIntent
        Intent notificationIntent = new Intent(this, NotificationSomething.class);
        notificationIntent.putExtra("notificationID",notification_id);
        notificationIntent.putExtra("extraString","Hello PendingIntent");
        PendingIntent contentIntent = PendingIntent.getActivity(this, 0, notificationIntent,PendingIntent.FLAG_UPDATE_CURRENT);

        Intent receiveIntent = new Intent(this, testReceiver.class);
        receiveIntent.putExtra("3351","Hello 3351~!");
        PendingIntent receivePendingIntent = PendingIntent.getBroadcast(this, 0, receiveIntent,PendingIntent.FLAG_UPDATE_CURRENT);

        // 반드시 채널 이름 추가해줄것! 그렇지않으면 channel null blabla.. 오류 뜸
        NotificationCompat.Builder builder = new NotificationCompat.Builder(this,CHANNEL_ID);

        builder.setContentTitle("Title")
                .setContentText("Sub title")
                .setTicker("Message")
                .setSmallIcon(R.drawable.ic_baseline_whatshot_24)
                .setContentIntent(contentIntent)
//                .setAutoCancel(true)
                .setWhen(System.currentTimeMillis())
                .setDefaults(Notification.DEFAULT_ALL)
                .addAction(R.drawable.ic_launcher_background,"contents",contentIntent)
                .addAction(R.drawable.ic_launcher_background,"check",receivePendingIntent);

        NotificationManager nm = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        nm.notify(notification_id,builder.build());
    }

    private void createNotificationChannel() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            CharSequence name = "1";
            int importance = NotificationManager.IMPORTANCE_DEFAULT;
            NotificationChannel channel = new NotificationChannel(CHANNEL_ID, name, importance);
            NotificationManager notificationManager = getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }
    }

}