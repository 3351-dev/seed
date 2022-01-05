package com.example.androidalarm;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;
import androidx.fragment.app.FragmentManager;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import java.util.ArrayList;
import java.util.List;

public class fragment_view_1 extends Fragment implements recyclerAdapter.RecyclerViewClickListener{

    private RecyclerView recyclerView;
    private List<CardItem> dataList;
    private recyclerAdapter mAdapter;
    private FragmentActivity myContext;
    private SharedPreferences mPreferences;
    private FloatingActionButton fab;
    private RelativeLayout rl1;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @NonNull ViewGroup container,
                             @NonNull Bundle savedInstanceState){
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_view_1, container, false);

        rl1 = rootView.findViewById(R.id.relative1);
        fab = (FloatingActionButton) rootView.findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int pos = 0;
                Log.d("fabClickTest", "fab click");
                for(int i=0;i<dataList.size();i++){
                    pos++;
                }
                onTitleClicked(pos);
            }
        });

        recyclerView = rootView.findViewById(R.id.connect_recyclerview);
        // RecyclerView Adapter
        recyclerAdapter recyclerAdapter = new recyclerAdapter(dataList,getContext());
        recyclerView.setLayoutManager(new LinearLayoutManager(getActivity()));
        recyclerView.setAdapter(recyclerAdapter);

        mAdapter = new recyclerAdapter(dataList,getContext());
        mAdapter.setOnClickListener(this);
        recyclerView.setAdapter(mAdapter);

//        mPreferences = PreferenceManager.getDefaultSharedPreferences(myContext);
        mPreferences = getActivity().getSharedPreferences("UserInfo", Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = mPreferences.edit();


        // Bundle
        if(getArguments()!= null){
            int pos=0;
            String hour, minute;
            hour = getArguments().getString("hour");
            minute = getArguments().getString("minute");
            Log.d("Fragment_view_1","bundle : "+hour);
            for(int i=0;i<dataList.size();i++){
                pos++;
            }
            dataList.add(new CardItem(hour+":"+minute,""+pos));
            editor.putString("TT", "value");
            editor.commit();
            getPreferences();
            // rootView가 아닌 container
            String str = mPreferences.getString("TT","");
            Snackbar.make(container.findViewById(R.id.relative1),"Snack",Snackbar.LENGTH_SHORT).show();

        }

        return rootView;
    }

    private void getPreferences() {
        dataList.add(new CardItem(mPreferences.getString("UserInfo","0"),"123"));
    }

    @Override
    public void onAttach(Activity activity){
        myContext = (FragmentActivity) activity;
        super.onAttach(activity);

    }

    // 어댑터 설정
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // 표시할 데이터
        dataList = new ArrayList<>();
        dataList.add(new CardItem("First","Android Boy"));
        dataList.add(new CardItem("Second","one\nTwo"));
        dataList.add(new CardItem("Third","1\n2\n3"));

    }

    public void onItemClicked(int position){
        Log.d(" ","Item : "+position);
    }

    public void onShareButtonClicked(int position){
        Log.d(" ", "share : "+position);
        //Item Add
        mAdapter.addItem(position+1, new CardItem("Add","Add"+position));
    }

    public void onDeleteButtonClicked(int position) {
        Log.d(" ","delete : " + position);
        mAdapter.removeItem(position);
    }

    @Override
    public void onTitleClicked(int position) {
        Log.d("fragment","title pos : "+position);
        FragmentManager fragmentManager = myContext.getSupportFragmentManager();
        TimePickerFragment timePickerFragment = new TimePickerFragment();
        // setTargetFragment use
//        timePickerFragment.setTargetFragment(this, 0);
        timePickerFragment.show(fragmentManager, " timePicker");

    }


}
