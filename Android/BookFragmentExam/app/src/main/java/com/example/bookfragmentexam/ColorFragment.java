package com.example.bookfragmentexam;

import android.graphics.Color;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.fragment.app.Fragment;

public class ColorFragment extends Fragment {
    private int mColor = Color.BLUE;
    private TextView mHelloTextView;
    public ColorFragment(){

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_color, container, false);
        mHelloTextView = (TextView) view.findViewById(R.id.hello_text);
        mHelloTextView.setBackgroundColor(mColor);
        return view;
    }

    public void setColor(int color){
        mColor = color;
        if(mHelloTextView != null){
            mHelloTextView.setBackgroundColor(color);
        }
    }
}
