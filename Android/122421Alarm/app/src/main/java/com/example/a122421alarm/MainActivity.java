package com.example.a122421alarm;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TimePicker;
import android.widget.Toast;

import java.util.Calendar;
import java.util.concurrent.TimeUnit;

public class MainActivity extends AppCompatActivity {

    private TimePicker tp;
    private AlarmManager alm;
    private int hour,minute;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tp = findViewById(R.id.tp_timepicker);

    }

    public void regist(View view){

        if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.M){
//            hour = tp.getCurrentHour();
//            minute = tp.getCurrentMinute();
            hour = tp.getHour();
            minute = tp.getMinute();
        }

        Calendar calendar = Calendar.getInstance();
//        calendar.setTimeInMillis(System.currentTimeMillis());
        calendar.set(Calendar.HOUR_OF_DAY,hour);
        calendar.set(Calendar.MINUTE,minute);
        calendar.set(Calendar.SECOND,0);

        alm = (AlarmManager) getSystemService(Context.ALARM_SERVICE);

        Intent intent = new Intent(this, alarm.class);
        PendingIntent pendingIntent = PendingIntent.getBroadcast(this,0,intent,0);

//        alm.setInexactRepeating(
//        alm.setWindow(
//          alm.setRepeating(
          alm.setExact(
                AlarmManager.RTC_WAKEUP,
//                AlarmManager.ELAPSED_REALTIME_WAKEUP,
                calendar.getTimeInMillis(),
                pendingIntent);
        Toast.makeText(this,"ok",Toast.LENGTH_SHORT).show();
        Log.d("3351", "start alarm "+hour + " "+minute+" ");
    }
    public void unresgist(View view){
        Intent intent = new Intent(this, alarm.class);
        PendingIntent pendingIntent;
        pendingIntent = PendingIntent.getBroadcast(this,0,intent,0);
    }
}