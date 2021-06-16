package com.kingkongjsc.ducvuongcity.kd201eviewer;

import android.app.Fragment;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.NavigationView;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;


public class SettingsFragment extends Fragment {
    private NavigationView.OnNavigationItemSelectedListener listener = null;
    private MenuItem item = null;
    private NavigationView navigationView = null;
    private MainActivity mainActivity = null;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.activity_settings, container, false);
        return view;
    }
}