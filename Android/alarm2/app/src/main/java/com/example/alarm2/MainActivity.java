package com.example.alarm2;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ShareActionProvider;
import android.widget.TimePicker;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final TimePicker picker = findViewById(R.id.timePicker);
        picker.setIs24HourView(true);

        SharedPreferences sharedPreferences = getSharedPreferences("daily alarm",MODE_PRIVATE);
        long millis = sharedPreferences.getLong("next Nofify Time", Calendar.getInstance().getTimeInMillis());

        Calendar nextNotifyTime = new GregorianCalendar();
        nextNotifyTime.setTimeInMillis(millis);

        Date nextDate = nextNotifyTime.getTime();
        String date_text = new SimpleDateFormat("yyyy MM dd EE a hh mm ", Locale.getDefault()).format(nextDate);
        Toast.makeText(getApplicationContext(),"Next Alarm : "+date_text,Toast.LENGTH_SHORT).show();

        Date currentTime = nextNotifyTime.getTime();
        SimpleDateFormat HourFormat = new SimpleDateFormat("kk",Locale.getDefault());
        SimpleDateFormat MinuteFormat = new SimpleDateFormat("mm",Locale.getDefault());

        int pre_hour = Integer.parseInt(HourFormat.format(currentTime));
        int pre_minute = Integer.parseInt(MinuteFormat.format(currentTime));

        if(Build.VERSION.SDK_INT>=23){
            picker.setHour(pre_hour);
            picker.setMinute(pre_minute);
        }else{
            picker.setCurrentHour(pre_hour);
            picker.setCurrentMinute(pre_minute);
        }

        Button button = findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View arg0){
                int hour, hour_24, minute;
                String am_pm;
                if(Build.VERSION.SDK_INT>=23) {
                    hour_24 = picker.getHour();
                    minute = picker.getMinute();
                }else{
                    hour_24 = picker.getCurrentHour();
                    minute = picker.getCurrentMinute();
                }

                if(hour_24>12){
                    am_pm="PM";
                    hour=hour_24-12;
                }else{
                    am_pm="AM";
                    hour = hour_24;
                }

                Calendar calendar = Calendar.getInstance();
                calendar.setTimeInMillis(System.currentTimeMillis());
                calendar.set(Calendar.HOUR_OF_DAY,hour_24);
                calendar.set(Calendar.MINUTE,minute);
                calendar.set(Calendar.SECOND,0);

                if(calendar.before((Calendar.getInstance()))){
                    calendar.add(Calendar.DATE,1);
                }

                Date currentDateTime= calendar.getTime();
                String date_text = new SimpleDateFormat("yyyy MM dd EE a hh mm",Locale.getDefault()).format(currentDateTime);
                Toast.makeText(getApplicationContext(),date_text+"alaram setting",Toast.LENGTH_SHORT).show();

                SharedPreferences.Editor editor = getSharedPreferences("daily alarm", MODE_PRIVATE).edit();
                editor.putLong("NextNotifyTime",calendar.getTimeInMillis());
                editor.apply();

                diaryNotification(calendar);
            }

        });

        
    }

    void diaryNotification(Calendar calendar){
        Boolean dailyNotify = true;

        PackageManager pm = this.getPackageManager();
        ComponentName receiver = new ComponentName(this, DeviceBootReceiver.class);
        Intent alarmIntent = new Intent(this, AlarmReceiver.class);
        PendingIntent pendingIntent = PendingIntent.getBroadcast(this,0,alarmIntent,0);
        AlarmManager alarmManager = (AlarmManager) getSystemService(Context.ALARM_SERVICE);

        if(alarmManager != null){
            alarmManager.setRepeating(AlarmManager.RTC_WAKEUP, calendar.getTimeInMillis(),AlarmManager.INTERVAL_DAY,pendingIntent);
            if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.M){
                alarmManager.setExactAndAllowWhileIdle(AlarmManager.RTC_WAKEUP,calendar.getTimeInMillis(),pendingIntent);
            }
        }
        pm.setComponentEnabledSetting(receiver,PackageManager.COMPONENT_ENABLED_STATE_ENABLED,PackageManager.DONT_KILL_APP);

    }
}