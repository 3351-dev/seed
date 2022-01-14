package com.example.bookfragmentexam;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        FragmentManager fm = getSupportFragmentManager();
//        ColorFragment cf = (ColorFragment) fm.findFragmentById(R.id.color_fragment);

//        cf.setColor(Color.BLUE);
    }

    public void change(View view) {
        ColorFragment fm = new ColorFragment();
        int red = new Random().nextInt(256);
        int green = new Random().nextInt(256);
        int blue = new Random().nextInt(256);

        fm.setColor(Color.rgb(red, green, blue));
        getSupportFragmentManager().beginTransaction()
                .replace(R.id.container, fm)
                .commit();
    }
}