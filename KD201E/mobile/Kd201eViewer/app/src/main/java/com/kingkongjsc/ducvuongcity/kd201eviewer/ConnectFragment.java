package com.kingkongjsc.ducvuongcity.kd201eviewer;

import android.app.AlertDialog;
import android.app.Fragment;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.provider.Settings;
import android.support.annotation.Nullable;
import android.support.design.widget.NavigationView;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import java.net.InetAddress;

public class ConnectFragment extends Fragment {
    private NavigationView.OnNavigationItemSelectedListener listener = null;
    private MenuItem item = null;
    private NavigationView navigationView = null;
    private MainActivity mainActivity = null;

    private InetAddress inet = null;
    private int port;

    private EditText etStationIP = null;
    private EditText etPort= null;
    private Button btnConnect = null;

    private boolean isConnected = false;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.activity_connect, container, false);
        etStationIP = (EditText)view.findViewById(R.id.etStationIP);
        etPort = (EditText)view.findViewById(R.id.etPort);
        btnConnect = (Button)view.findViewById(R.id.btnConnect);
        btnConnect.setOnClickListener(connectClicked);

        navigationView = (NavigationView)getActivity().findViewById(R.id.nav_view);

        item = navigationView.getMenu().getItem(2);
        listener = (NavigationView.OnNavigationItemSelectedListener)getActivity();

        mainActivity = (MainActivity)getActivity();

        return view;
    }

    View.OnClickListener connectClicked = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            if (!isConnectedLAN()) {
                final AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
                builder.setTitle("Notify");
                builder.setMessage("Not connect to network, open network connection settings?");
                builder.setPositiveButton("Settings", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        startActivity(new Intent(Settings.ACTION_WIFI_SETTINGS));
                    }
                });
                builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                });
                builder.show();
            }

            else {
                final ProgressDialog progress = new ProgressDialog(getActivity());
                progress.setProgressStyle(ProgressDialog.STYLE_SPINNER);
                progress.setMessage("Connectting...");
                progress.show();
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        getActivity().runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                try {
                                    inet = InetAddress.getByName(etStationIP.getText().toString());
                                    port = Integer.parseInt(etPort.getText().toString());
                                    if (mainActivity.connectStation(inet, port)) {
                                        mainActivity.isConnetedStation = true;
                                        listener.onNavigationItemSelected(item);
                                    }
                                    else
                                        Toast.makeText(getActivity(), "Can't connect to station", Toast.LENGTH_LONG).show();
                                }catch (Exception e){
                                    Toast.makeText(getActivity(), "Error " + e.toString(), Toast.LENGTH_LONG).show();
                                }
                                progress.dismiss();
                            }
                        });
                    }
                }).start();
            }
        }
    };

    //region Check network connect
    private boolean isConnectedLAN() {
        ConnectivityManager connManager = (ConnectivityManager)getActivity().getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo mWifi = connManager.getActiveNetworkInfo();

        if (mWifi != null && mWifi.isConnected()) {
            return true;
        }
        return false;
    }
    //endregion

    //region Check station connect
    public boolean isConnectedStation() {
        return isConnected;
    }
    //endregion
}