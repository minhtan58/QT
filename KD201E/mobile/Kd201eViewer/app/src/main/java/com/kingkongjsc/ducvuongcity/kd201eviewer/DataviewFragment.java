package com.kingkongjsc.ducvuongcity.kd201eviewer;

import android.app.Fragment;
import android.content.Context;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.NavigationView;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;


public class DataviewFragment extends Fragment {
    private NavigationView.OnNavigationItemSelectedListener listener = null;
    private MenuItem item = null;
    private NavigationView navigationView = null;
    private MainActivity mainActivity = null;

    private EditText etSend = null;
    private Button btnSend = null;
    private EditText etReceiver = null;

    private EditText edtId01Val1 = null;
    private EditText edtId01Val2 = null;
    private EditText edtId02Val1 = null;
    private EditText edtId02Val2 = null;
    private EditText edtId03Val1 = null;
    private EditText edtId03Val2 = null;
    private EditText edtId04Val1 = null;
    private EditText edtId04Val2 = null;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.activity_dataview, container, false);
        etSend = (EditText)view.findViewById(R.id.etSend);
        btnSend = (Button)view.findViewById(R.id.btnSend);
        btnSend.setOnClickListener(sendClicked);
        etReceiver = (EditText)view.findViewById(R.id.etReceiver);

        edtId01Val1 = (EditText)view.findViewById(R.id.edtId01Val1);
        edtId01Val2 = (EditText)view.findViewById(R.id.edtId01Val2);
        edtId02Val1 = (EditText)view.findViewById(R.id.edtId02Val1);
        edtId02Val2 = (EditText)view.findViewById(R.id.edtId02Val2);
        edtId03Val1 = (EditText)view.findViewById(R.id.edtId03Val1);
        edtId03Val2 = (EditText)view.findViewById(R.id.edtId03Val2);
        edtId04Val1 = (EditText)view.findViewById(R.id.edtId04Val1);
        edtId04Val2 = (EditText)view.findViewById(R.id.edtId04Val2);

        navigationView = (NavigationView)getActivity().findViewById(R.id.nav_view);
        listener = (NavigationView.OnNavigationItemSelectedListener)getActivity();
        mainActivity = (MainActivity)getActivity();

        return view;
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        final InputMethodManager imm = (InputMethodManager) getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
        imm.hideSoftInputFromWindow(getView().getWindowToken(), 0);
        if (mainActivity.isConnetedStation)
            mainActivity.receiverDataView(etReceiver, edtId01Val1, edtId01Val2, edtId02Val1, edtId02Val2, edtId03Val1, edtId03Val2, edtId04Val1, edtId04Val2);
    }

    View.OnClickListener sendClicked = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            if (mainActivity.isConnetedStation) {
                mainActivity.sendData(etSend.getText().toString());
                etSend.setText("");
            }
        }
    };
}