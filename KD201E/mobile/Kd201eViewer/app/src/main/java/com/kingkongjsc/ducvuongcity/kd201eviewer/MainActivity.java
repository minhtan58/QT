package com.kingkongjsc.ducvuongcity.kd201eviewer;

import android.app.FragmentManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.StrictMode;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.support.v7.app.ActionBarDrawerToggle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.Toast;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.lang.ref.WeakReference;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {
    private NavigationView navigationView = null;
    private FragmentManager fmm = null;
    private ConnectFragment fmConnect= null;
    private DataviewFragment fmDataview = null;
    private SettingsFragment fmSettings = null;
    private AboutFragment fmAbout = null;

    private static Socket clientSocket = null;
    private static PrintWriter clientSend = null;
    private static InputStream clientReceiver = null;

    private static Timer updateTimer = null;

    //drawer navigation item
    private MenuItem navConnect = null;
    private MenuItem navDataview = null;
    private MenuItem navSettings = null;
    private MenuItem navAbout = null;

    public boolean isConnetedStation = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //fix Network on Main Thread
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        //region init fragment
        fmm = getFragmentManager();
        fmConnect = new ConnectFragment();
        fmDataview = new DataviewFragment();
        fmSettings = new SettingsFragment();
        fmAbout = new AboutFragment();
        //endregion

        TimerTask updateValue = new TimerTask() {
            @Override
            public void run() {
                if (clientSocket != null)
                    if (clientSocket.isConnected())
                        sendData("update");
            }
        };
        updateTimer = new Timer();
        updateTimer.schedule(updateValue, 1000, 5000);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.setDrawerListener(toggle);
        toggle.syncState();

        navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);

        //region Khởi tạo các item của navigation drawer
        navConnect = navigationView.getMenu().findItem(R.id.navConnect);
        navDataview = navigationView.getMenu().findItem(R.id.navDataview);
        navSettings = navigationView.getMenu().findItem(R.id.navSettings);
        navAbout = navigationView.getMenu().findItem(R.id.navAbout);
        //endregion

        clientSocket = new Socket();

        onNavigationItemSelected(navConnect);
    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();

        if (id == R.id.navConnect) {
            fmm.beginTransaction().replace(R.id.rlMain, fmConnect).commit();
        } else if (id == R.id.navDataview) {
            fmm.beginTransaction().replace(R.id.rlMain, fmDataview).commit();
        } else if (id == R.id.navSettings) {
            fmm.beginTransaction().replace(R.id.rlMain, fmSettings).commit();
        } else if (id == R.id.navAbout) {
            fmm.beginTransaction().replace(R.id.rlMain, fmAbout).commit();
        }

        item.setChecked(true);

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

    public boolean connectStation(InetAddress inet, int port)
    {
        try {
            if (clientSocket.isConnected()) {
                clientSocket.close();
                clientSend.close();
                clientReceiver.close();
            }

            try {
                clientSocket = new Socket();
                clientSocket.connect(new InetSocketAddress(inet, port), 5000);
                clientSend = new PrintWriter(new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream())), true);
                return true;
            } catch (Exception e) {
                Toast.makeText(this, "Can't connect to "
                        + inet.getHostAddress() + ":" + port + "\n"
                        + e.toString(), Toast.LENGTH_LONG).show();
            }

        }catch (Exception e){
            Toast.makeText(this, e.toString(), Toast.LENGTH_LONG).show();
        }
        return false;
    }

    public boolean disconnectStation() {
        if (clientSocket.isConnected()) {
            try {
                clientSocket.close();
                if (clientSend != null)
                    clientSend.close();
                if (clientReceiver != null)
                    clientReceiver.close();
                Toast.makeText(this, "Disconnected", Toast.LENGTH_LONG).show();
            } catch (IOException e) {
                Toast.makeText(this, "Can't disconnect, error " + e.toString(), Toast.LENGTH_LONG).show();
                return false;
            }
        }
        return true;
    }

    public void sendData(String data)
    {
        clientSend.printf("%s",data);
    }

    public void receiverDataView(EditText edtId01Val1, EditText edtId01Val2, EditText edtId02Val1, EditText edtId02Val2, EditText edtId03Val1, EditText edtId03Val2, EditText edtId04Val1, EditText edtId04Val2)
    {
        InternetTask task = new InternetTask(edtId01Val1, edtId01Val2, edtId02Val1, edtId02Val2, edtId03Val1, edtId03Val2, edtId04Val1, edtId04Val2);
        task.execute();
    }

    public void receiverDataView(EditText edt, EditText edtId01Val1, EditText edtId01Val2, EditText edtId02Val1, EditText edtId02Val2, EditText edtId03Val1, EditText edtId03Val2, EditText edtId04Val1, EditText edtId04Val2) {
        InternetTask task = new InternetTask(edt, edtId01Val1, edtId01Val2, edtId02Val1, edtId02Val2, edtId03Val1, edtId03Val2, edtId04Val1, edtId04Val2);
        task.execute();
    }

    //region Task nhận data
    public class InternetTask extends AsyncTask<Void, Integer, Void> {
        private WeakReference<EditText> edtCmd = null;
        private WeakReference<EditText> edtId01Val1 = null;
        private WeakReference<EditText> edtId01Val2 = null;
        private WeakReference<EditText> edtId02Val1 = null;
        private WeakReference<EditText> edtId02Val2 = null;
        private WeakReference<EditText> edtId03Val1 = null;
        private WeakReference<EditText> edtId03Val2 = null;
        private WeakReference<EditText> edtId04Val1 = null;
        private WeakReference<EditText> edtId04Val2 = null;

        private String message;

        public InternetTask(EditText edtId01Val1, EditText edtId01Val2, EditText edtId02Val1, EditText edtId02Val2, EditText edtId03Val1, EditText edtId03Val2, EditText edtId04Val1, EditText edtId04Val2) {
            this.edtId01Val1 = new WeakReference<EditText>(edtId01Val1);
            this.edtId01Val2 = new WeakReference<EditText>(edtId01Val2);
            this.edtId02Val1 = new WeakReference<EditText>(edtId02Val1);
            this.edtId02Val2 = new WeakReference<EditText>(edtId02Val2);
            this.edtId03Val1 = new WeakReference<EditText>(edtId03Val1);
            this.edtId03Val2 = new WeakReference<EditText>(edtId03Val2);
            this.edtId04Val1 = new WeakReference<EditText>(edtId04Val1);
            this.edtId04Val2 = new WeakReference<EditText>(edtId04Val2);
            this.message = "";
        }

        public InternetTask(EditText edtCmd, EditText edtId01Val1, EditText edtId01Val2, EditText edtId02Val1, EditText edtId02Val2, EditText edtId03Val1, EditText edtId03Val2, EditText edtId04Val1, EditText edtId04Val2) {
            this.edtCmd = new WeakReference<EditText>(edtCmd);
            this.edtId01Val1 = new WeakReference<EditText>(edtId01Val1);
            this.edtId01Val2 = new WeakReference<EditText>(edtId01Val2);
            this.edtId02Val1 = new WeakReference<EditText>(edtId02Val1);
            this.edtId02Val2 = new WeakReference<EditText>(edtId02Val2);
            this.edtId03Val1 = new WeakReference<EditText>(edtId03Val1);
            this.edtId03Val2 = new WeakReference<EditText>(edtId03Val2);
            this.edtId04Val1 = new WeakReference<EditText>(edtId04Val1);
            this.edtId04Val2 = new WeakReference<EditText>(edtId04Val2);
            this.message = "";
        }

        public InternetTask(EditText edt) {
            this.edtCmd = new WeakReference<EditText>(edt);
            this.message = "";
        }

        @Override
        protected Void doInBackground(Void... params) {
            try {
                clientReceiver = clientSocket.getInputStream();

                byte[] buffer = new byte[500];
                int read = clientReceiver.read(buffer);
                while(read != -1){
                    message = new String(buffer);
                    publishProgress(read);
                    read = clientReceiver.read(buffer);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            return null;
        }

        @Override
        protected void onProgressUpdate(Integer... values) {
            if(values.length > 0){
                if (edtCmd != null) {
                    String old = edtCmd.get().getText().toString();
                    edtCmd.get().setText(old + "\n" + message);
                }
                updateDataView(message);
            }
        }

        private void updateDataView(String msg) {
            String[] elements = msg.split(",");
            if (elements.length > 12 && elements[0].contains("update")) {
                if (edtId01Val1 != null &&
                        edtId01Val2 != null &&
                        edtId02Val1 != null &&
                        edtId02Val2 != null &&
                        edtId03Val1 != null &&
                        edtId04Val1 != null &&
                        edtId04Val2 != null) {
                    edtId01Val1.get().setText(elements[5]);
                    edtId01Val2.get().setText(elements[6]);
                    edtId02Val1.get().setText(elements[7]);
                    edtId02Val2.get().setText(elements[8]);
                    edtId03Val1.get().setText(elements[9]);
                    edtId03Val2.get().setText(elements[10]);
                    edtId04Val1.get().setText(elements[11]);
                    edtId04Val2.get().setText(elements[12]);
                }
            }
        }

    }
    //endregion
}
