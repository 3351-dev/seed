package com.example.alarm2;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Locale;
import java.util.Objects;

public class DeviceBootReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent){
        if(Objects.equals(intent.getAction(),"android.intent.action.BOOT_COMPLETED")){
            Intent alarmIntent = new Intent(context, AlarmReceiver.class);
            PendingIntent pendingIntent = PendingIntent.getBroadcast(context,0,alarmIntent,0);

            AlarmManager manager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);

            SharedPreferences sharedPreferences = context.getSharedPreferences("daily alarm",Context.MODE_PRIVATE);
            long millis = sharedPreferences.getLong("NextNotifyTime", Calendar.getInstance().getTimeInMillis());

            Calendar current_calendar = Calendar.getInstance();
            Calendar nextNotifyTime = new GregorianCalendar();
            nextNotifyTime.setTimeInMillis(sharedPreferences.getLong("nextNotifyTime",millis));

            if(current_calendar.after(nextNotifyTime)){
                nextNotifyTime.add(Calendar.DATE,1);
            }

            Date currentDateTime = nextNotifyTime.getTime();
            String date_text = new SimpleDateFormat("yyyy MM dd EE a hh mm ", Locale.getDefault()).format(currentDateTime);
            Toast.makeText(context.getApplicationContext(),"Next alarm is "+date_text,Toast.LENGTH_SHORT).show();

            if(manager!=null){
                manager.setRepeating(AlarmManager.RTC_WAKEUP, nextNotifyTime.getTimeInMillis(),AlarmManager.INTERVAL_DAY,pendingIntent);
            }
        }
    }
}
