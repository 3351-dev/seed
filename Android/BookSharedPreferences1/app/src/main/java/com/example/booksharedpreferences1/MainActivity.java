package com.example.booksharedpreferences1;

import androidx.appcompat.app.AppCompatActivity;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

public class MainActivity extends AppCompatActivity {

    private EditText mEmailEditText;
    private CheckBox mSaveCheckBox;
    private SharedPreferences mPreferences;
    private Button mLoginButton;
    private TextView mId_tv;
    private FloatingActionButton fab;
    private LinearLayout ll1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mEmailEditText=(EditText) findViewById(R.id.email_edit);
        mSaveCheckBox=(CheckBox) findViewById(R.id.save_check);
        mLoginButton=(Button)findViewById(R.id.login_btn);
        mId_tv=(TextView)findViewById(R.id.id_tv);
        fab = (FloatingActionButton) findViewById(R.id.fab);
        ll1 = findViewById(R.id.linear1);

//        mPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        mPreferences = getSharedPreferences("UserInfo",MODE_PRIVATE);

        /*Boolean isChecked = mPreferences.getBoolean("save", false);
        mSaveCheckBox.setChecked(isChecked);
        if(isChecked){
            String email = mPreferences.getString("email", "");
            mEmailEditText.setText(email);
        }*/

        mLoginButton.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view) {
                SharedPreferences.Editor editor = mPreferences.edit();
                if(mSaveCheckBox.isChecked()) {
                    editor.putString("userid", mEmailEditText.getText().toString());
                    editor.commit();
                    getPreferences();
                }else{
                    editor.putString("userid","Null");
                    editor.apply();
                    getPreferences();
                }
            }
        });

        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.d("Test", "1");
                Snackbar.make(ll1, "test", Snackbar.LENGTH_SHORT).show();
            }
        });






    }

    private void getPreferences() {
        mId_tv.setText("User ID : "+mPreferences.getString("userid",""));


    }

}