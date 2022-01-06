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
import androidx.fragment.app.FragmentTransaction;
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
    private FloatingActionButton fab2;  //test button
    private RelativeLayout rl1;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @NonNull ViewGroup container,
                             @NonNull Bundle savedInstanceState){
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_view_1, container, false);

        mAdapter = new recyclerAdapter(dataList,getContext());
        mAdapter.setOnClickListener(this);

        rl1 = rootView.findViewById(R.id.relative1);
        fab = (FloatingActionButton) rootView.findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int pos = mAdapter.getItemCount()+1;
                Log.d("fabClickTest", "pos:"+pos);
                // Todo
                for(int i=0;i<10;i++){
                    String count = mPreferences.getString(String.valueOf(i),"");
                }
                onTitleClicked(pos);
            }
        });

        fab2 = rootView.findViewById(R.id.fab2);
        fab2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mPreferences = getActivity().getSharedPreferences("alarm", Context.MODE_PRIVATE);
                SharedPreferences.Editor editor= mPreferences.edit();
                int amountCount = mAdapter.getItemCount();
                Log.d("getItemCount",">>>"+mAdapter.getItemCount());
                for(int i=0;i<10;i++){
                    int j=0;
                    editor.remove(String.valueOf(i));
                    if(i<amountCount) {
                        mAdapter.removeItem(j);
                        Log.d("removeItem","ok");
                        j++;
                    }
                }
                editor.apply();

            }
        });

        recyclerView = rootView.findViewById(R.id.connect_recyclerview);
        // RecyclerView Adapter
//        recyclerAdapter recyclerAdapter = new recyclerAdapter(dataList,getContext());
        recyclerView.setLayoutManager(new LinearLayoutManager(getActivity()));
//        recyclerView.setAdapter(recyclerAdapter);


        recyclerView.setAdapter(mAdapter);

        // Preferences Setting
//        mPreferences = PreferenceManager.getDefaultSharedPreferences(myContext);
        mPreferences = getActivity().getSharedPreferences("alarm", Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = mPreferences.edit();

        // Bundle
        if(getArguments()!= null){
            int pos=0;
            String hour, minute;
            hour = getArguments().getString("hour");
            minute = getArguments().getString("minute");


            pos = mAdapter.getItemCount();      //(error) pos = 0
            Log.d("Bundle getItemCount",""+pos);

            String value = hour+":"+minute;
            editor.putString(String.valueOf(pos), value);
            editor.apply();
            // rootView가 아닌 container
//            Snackbar.make(container.findViewById(R.id.relative1),str,Snackbar.LENGTH_SHORT).show();

        }
        getPreferences();

        return rootView;
    }

    private void getPreferences() {
        for(int i=0;i<10;i++){
            String data = mPreferences.getString(String.valueOf(i),"");
            if(data != ""){
                dataList.add(new CardItem(data,String.valueOf(i)));
            }
        }
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

        /*dataList.add(new CardItem("0","0"));
        dataList.add(new CardItem("1","1"));
        dataList.add(new CardItem("2","2"));*/
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
        mPreferences = getActivity().getSharedPreferences("alarm", Context.MODE_PRIVATE);
        SharedPreferences.Editor editor= mPreferences.edit();
        editor.remove(String.valueOf(position));
        editor.apply();
        Log.d("Preferences Remove",""+position);
    }

    @Override
    public void onTitleClicked(int position) {
//        Log.d("fragment","title pos : "+position);
        /*----------------------------------------------------------------------*/
        // Bundle
        int ItemCount = mAdapter.getItemCount();
        Bundle bundle = new Bundle();
        bundle.putInt("switch",position);
        bundle.putInt("Count",ItemCount);
        FragmentTransaction transaction = getActivity().getSupportFragmentManager().beginTransaction();
        TimePickerFragment tp = new TimePickerFragment();
        tp.setArguments(bundle);
        transaction.commit();
        /*----------------------------------------------------------------------*/

        FragmentManager fragmentManager = myContext.getSupportFragmentManager();
        TimePickerFragment timePickerFragment = new TimePickerFragment();
        timePickerFragment.show(fragmentManager, " timePicker");
    }


}
