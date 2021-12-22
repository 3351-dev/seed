package com.example.activityexam;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    public static final int REQUEST_CODE = 1000;
    private EditText mNameEditText;
    private EditText mAgeEditText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mNameEditText = findViewById(R.id.name_edit);
        mAgeEditText = findViewById(R.id.age_edit);

//        findViewById(R.id.submit_button).setOnClickListener(this);

        Button btn = findViewById(R.id.submit_button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(), SecondActivity.class);
                intent.putExtra("name", mNameEditText.getText().toString());
                intent.putExtra("age",mAgeEditText.getText().toString());
                startActivityForResult(intent, REQUEST_CODE);
            }
        });
    }
/*
    @Override
    public void OnClick(View v){
        Intent intent = new Intent(this, SecondActivity.class);
        intent.putExtra("name", mNameEditText.getText().toString());
        intent.putExtra("age",mAgeEditText.getText().toString());
        startActivityForResult(intent, REQUEST_CODE);
    }
 */

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        super.onActivityResult(requestCode, resultCode, data);
        if(requestCode==RESULT_OK&&resultCode==RESULT_OK&&data!=null){
            String result = data.getStringExtra("result");
            Toast.makeText(MainActivity.this, result, Toast.LENGTH_SHORT).show();
        }
    }
}