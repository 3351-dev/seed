package com.example.a122421alarm;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

public class alarm extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent){
        Toast.makeText(context,"Ring Ring",Toast.LENGTH_SHORT).show();
        Log.e("Ring Ring","ring");
    }
}
