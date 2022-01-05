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

import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentTransaction;

import java.util.Calendar;

public class TimePickerFragment extends DialogFragment implements TimePickerDialog.OnTimeSetListener{

    private AlarmManager mAlarmManager;
/*
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        View view = inflater.inflate(R.layout.item_card,container,false);
        TextView title = (TextView) view.findViewById(R.id.title_text);

        title.setText("123");

        return view;
    }

 */



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
        LayoutInflater inflater = getLayoutInflater();
        View v1 = inflater.inflate(R.layout.item_card,null);
        TextView title = (TextView) v1.findViewById(R.id.title_text);

        Log.d("Before",""+title.getText());
        // 설정된 시간
        Calendar calendar = Calendar.getInstance();
        calendar.set(Calendar.HOUR_OF_DAY, hourOfDay);
        calendar.set(Calendar.MINUTE,minute);


        Toast.makeText(this.getContext(),""+hourOfDay+" "+minute,Toast.LENGTH_SHORT).show();

        Intent intent = new Intent(getContext(), recyclerAdapter.class);
        PendingIntent operation = PendingIntent.getActivity(getContext(), 0, intent, 0);

        mAlarmManager.set(AlarmManager.RTC_WAKEUP, calendar.getTimeInMillis(), operation);
        /*----------------------------------------------------------------------*/

        /*title.setText(hourOfDay + " : " +minute);
        Log.d("After",""+title.getText());*/

        // Bundle use
        Bundle bundle = new Bundle();
        bundle.putString("hour", String.valueOf(hourOfDay));
        bundle.putString("minute", String.valueOf(minute));
        Log.d("Bundle Test","bundle : "+bundle);
        FragmentTransaction transaction = getActivity().getSupportFragmentManager().beginTransaction();
        fragment_view_1 fragment_view_1 = new fragment_view_1();
        fragment_view_1.setArguments(bundle);
        transaction.replace(R.id.container, fragment_view_1);
        transaction.commit();
    }

}
