package com.example.activityexam;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class SecondActivity extends AppCompatActivity {
    private TextView mMessageTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);

        Intent intent = getIntent();
        String name = intent.getStringExtra("name");
        String age = intent.getStringExtra("age");

        mMessageTextView = findViewById(R.id.message_edit_text);
        mMessageTextView.setText(age +"years"+name);

//        findViewById(R.id.result_button).setOnClickListener((View.OnClickListener) this);
        Button btn = findViewById(R.id.result_button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent();
                intent.putExtra("result",mMessageTextView.getText().toString());
                setResult(RESULT_OK, intent);
                finish();
            }
        });
    }
    /*
    @Override
    public void OnClick(View v){
        Intent intent = new Intent();
        intent.putExtra("result",mMessageTextView.getText().toString());
        setResult(RESULT_OK, intent);
        finish();
    }
     */
}