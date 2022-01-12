package com.example.androidalarm;

import android.app.Service;
import android.content.Intent;
import android.content.SharedPreferences;
import android.media.MediaPlayer;
import android.os.Binder;
import android.os.Build;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;

import androidx.annotation.Nullable;

public class ServiceTest extends Service {
//    private final String TAG = this.getClass().getSimpleName().trim().substring(0,22);
    private final String TAG = this.getClass().getSimpleName();
    private final IBinder mBinder = new LocalBinder();
    SharedPreferences mPreferences;
    MediaPlayer mp;

    class LocalBinder extends Binder{
        ServiceTest getService(){
            return ServiceTest.this;
        }
    }


    @Nullable
    @Override
    public IBinder onBind(Intent intent) {

        String extraData="";
        Bundle extras = intent.getExtras();
        if(extras == null){
            extraData = "error";
            Log.d(TAG, ""+extraData );
        }else{
            extraData = extras.getString("value");
            Log.d(TAG, ""+extraData );
        }

        return mBinder;
    }

    @Override
    public void onCreate(){
        Log.d(TAG,"Create");
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId){
        Log.d(TAG,"StartCommand");
        return super.onStartCommand(intent,flags,startId);
    }

    @Override
    public void onDestroy(){
        super.onDestroy();
        Log.d(TAG,"Destroy");
    }

}
