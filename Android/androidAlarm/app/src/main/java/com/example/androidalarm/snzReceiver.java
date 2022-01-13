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
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Switch;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import java.util.List;
import java.util.prefs.Preferences;

public class snzReceiver extends BroadcastReceiver{
    private final String TAG = this.getClass().getSimpleName();
    public final int NOTIFICATION_ID = 1;
    SharedPreferences mPreferences;

    @SuppressLint("ResourceType")
    @Override
    public void onReceive(Context context, Intent intent) {

        // preferences
        mPreferences = context.getSharedPreferences("alarm",Context.MODE_PRIVATE);
        SharedPreferences.Editor editor= mPreferences.edit();
        String pos = intent.getStringExtra("pos");
        Log.d(TAG,"it's snzReceiver here. "+pos);
        editor.putString(pos+"onOff","off");
        editor.apply();
/*
        LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View view = inflater.inflate(R.layout.fragment_view_1,null);
        Switch onOff = (Switch)view.findViewById(R.id.OnOff_btn);
        boolean on = onOff.isChecked();
        if(on){
            Log.d(TAG,"switch status on");
        }else{
            Log.d(TAG,"switch status off");
        }
*/
        context.sendBroadcast(new Intent("snz"));

        NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        notificationManager.cancel(Integer.parseInt(pos));

    }

}
