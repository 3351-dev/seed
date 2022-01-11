package com.example.pendingintenttest;

import android.app.NotificationManager;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class NotificationSomething extends AppCompatActivity {

    @Override
    public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.notification_something);

        Log.d("NotificationSomethings","Im here");

        CharSequence s = "Receive Value";
        int id =0;
        String extraData ="";

        Bundle extras = getIntent().getExtras();
        if(extras == null) {
            s = "error";
        }else{
//            id = extras.getInt("value");
            id = extras.getInt("notificationID");
            extraData = extras.getString("extraString");
        }

        TextView t = (TextView) findViewById(R.id.textView);
        s = s +" "+ extraData + "id : " +id;

        t.setText(s);
        NotificationManager nm = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

        nm.cancel(id);
    }

}
