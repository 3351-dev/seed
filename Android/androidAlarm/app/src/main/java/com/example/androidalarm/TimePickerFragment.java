package com.example.androidalarm;

import android.app.Activity;
import android.app.AlarmManager;
import android.app.Dialog;
import android.app.PendingIntent;
import android.app.TimePickerDialog;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.text.format.DateFormat;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.TimePicker;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentTransaction;

import java.util.Calendar;

public class TimePickerFragment extends DialogFragment implements TimePickerDialog.OnTimeSetListener{

    private AlarmManager mAlarmManager;

    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {

        // 알람 매니저 인스턴스 얻기
        mAlarmManager = (AlarmManager) getContext().getSystemService(Context.ALARM_SERVICE);

        // 현재 시간으로 TimePicker 설정
        final Calendar calendar = Calendar.getInstance();
        int hour = calendar.get(Calendar.HOUR_OF_DAY);
        int minute = calendar.get(Calendar.MINUTE);

        //  TimePickerDialog 현재 시간으로 설정하고 반환
        return new TimePickerDialog(getActivity(), this, hour, minute,
                DateFormat.is24HourFormat(getActivity()));
    }

    @Override
    public void onTimeSet(TimePicker timePicker, int hourOfDay, int minute) {
        /*----------------------------------------------------------------------*/
        int pos=0, ItemCount=0;
        // 설정된 시간
        Calendar calendar = Calendar.getInstance();
        calendar.set(Calendar.HOUR_OF_DAY, hourOfDay);
        calendar.set(Calendar.MINUTE,minute);
        calendar.set(Calendar.SECOND,0);


        Toast.makeText(this.getContext(),""+hourOfDay+" "+minute,Toast.LENGTH_SHORT).show();

//        PendingIntent operation = PendingIntent.getActivity(getContext(), 0, intent, 0);
        Intent intent = new Intent(getContext(), alarmReceiver.class);
        PendingIntent operation = PendingIntent.getBroadcast(getContext(), 0, intent, 0);

        /*mAlarmManager.setExact(AlarmManager.RTC_WAKEUP,
                calendar.getTimeInMillis(),
                operation);*/
        /*----------------------------------------------------------------------*/
        /*title.setText(hourOfDay + " : " +minute);
        Log.d("After",""+title.getText());*/

        /*----------------------------------------------------------------------*/
        // Bundle Get
        if(getArguments()!=null){

            pos = getArguments().getInt("pos");
            ItemCount = getArguments().getInt("ItemCount");
            Log.d("TP getArguments","pos : "+pos+" ItemCount : "+ItemCount);
        }else{
            Log.d("TP getArguments","nothing");
        }
        /*----------------------------------------------------------------------*/
        // Bundle Send
        Bundle bundle = new Bundle();
        bundle.putString("hour", String.valueOf(hourOfDay));
        bundle.putString("minute", String.format("%02d",minute));
        bundle.putString("pos",String.valueOf(pos));
        Log.d("Bundle Test","bundle : "+bundle);
        FragmentTransaction transaction = getActivity().getSupportFragmentManager().beginTransaction();
        fragment_view_1 fragment_view_1 = new fragment_view_1();
        fragment_view_1.setArguments(bundle);
        transaction.replace(R.id.container, fragment_view_1);
        transaction.commit();

    }



}