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

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @NonNull ViewGroup container,
                             @NonNull Bundle savedInstanceState){
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_view_1, container, false);

        mAdapter = new recyclerAdapter(dataList,getContext());
        mAdapter.setOnClickListener(this);

        mPreferences = getActivity().getSharedPreferences("alarm", Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = mPreferences.edit();

        fab = (FloatingActionButton) rootView.findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int pos = mAdapter.getItemCount();
                String temp = "10:00";
                Log.d("fabClickTest", "pos:"+pos);
                // Todo
                mAdapter.addItem(pos, new CardItem(temp,"contents"));

                editor.putString(String.valueOf(pos), temp);
                editor.putString(String.valueOf(pos)+"contents","contents");
                editor.apply();

//                onTitleClicked(pos);
            }
        });

        fab2 = rootView.findViewById(R.id.fab2);
        fab2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                int amountCount = mAdapter.getItemCount();
                Log.d("getItemCount",">>> "+mAdapter.getItemCount());
                for(int i=0;i<10;i++){
                    int j=0;
                    editor.remove(String.valueOf(i));
                    editor.remove(String.valueOf(i)+"onOff");
                    if(i<amountCount) {
                        mAdapter.removeItem(j);
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
//        mPreferences = getActivity().getSharedPreferences("alarm", Context.MODE_PRIVATE);

        // Bundle
        if(getArguments()!= null){
            String pos;
            String hour, minute;
            hour = getArguments().getString("hour");
            minute = getArguments().getString("minute");
            pos = getArguments().getString("pos");

//            pos = mAdapter.getItemCount();      //(error) pos = 0
//            Log.d("Bundle getItemCount",""+pos);

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
                dataList.add(new CardItem(data,mPreferences.getString(String.valueOf(i)+"contents","")));
            }
        }
    }

    @Override
    public void onAttach(@NonNull Activity activity){
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
//        Log.d("onCreate","ItemCount : "+mAdapter.getItemCount());
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
        int beforeCount, afterCount;
        beforeCount = mAdapter.getItemCount();
        Log.d("Delete","\t delete : " + position + "\tPreferences : "+mPreferences.getString(String.valueOf(position),""));
        mAdapter.removeItem(position);
        mPreferences = getActivity().getSharedPreferences("alarm", Context.MODE_PRIVATE);
        SharedPreferences.Editor editor= mPreferences.edit();
        editor.remove(String.valueOf(position));
        editor.remove(String.valueOf(position)+"onOff");
        editor.apply();
        afterCount = mAdapter.getItemCount();

        for(int i=0;i<afterCount;i++){
            if(mPreferences.getString(String.valueOf(i),"")==""){
                for(int j=0;j<beforeCount;j++){
                    if(mPreferences.getString(String.valueOf(j),"")==""){
                        editor.putString(String.valueOf(j),mPreferences.getString(String.valueOf(j+1),""));
                        editor.remove(String.valueOf(j+1));
                        editor.apply();
                    }
                }
            }
        }
        Log.d("Preferences Remove",""+position);
//        getString(String.valueOf(i),"");
    }

    @Override
    public void onTitleClicked(int position) {
        SharedPreferences.Editor editor = mPreferences.edit();
        editor.putString(String.valueOf(position)+"onOff","");
        editor.apply();

//        Log.d("fragment","title pos : "+position);
        /*----------------------------------------------------------------------*/
        // Bundle
        int ItemCount = mAdapter.getItemCount();
        Bundle bundle = new Bundle();
        bundle.putInt("pos",position);
        bundle.putInt("ItemCount",ItemCount);

        /*----------------------------------------------------------------------*/

        FragmentManager fragmentManager = myContext.getSupportFragmentManager();
        TimePickerFragment timePickerFragment = new TimePickerFragment();
        timePickerFragment.show(fragmentManager, " timePicker");
        // Bundle
        timePickerFragment.setArguments(bundle);
    }
}
