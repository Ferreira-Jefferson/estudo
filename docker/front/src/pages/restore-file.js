import { useEffect, useState } from "react";
import Header from "../components/Home/Header";
import RestoreProgress from "../components/Home/RestoreProgress";
import { useAppContext } from "../context/AppContext";

export default function RestoreFile() {
  const [restore, setRestore] = useState(false);
  const [progress, setProgress] = useState(0);
  const { navigateToNewPage } = useAppContext();

  useEffect(() => {
    const restoreFile = async () => {
      runProgress();
      await startRestore();
      navigateToNewPage("/");
    };
    restoreFile();
  }, []);

  const startRestore = async () => {
    setRestore(true);
    await fetch("/api/restore");
  };

  const runProgress = (step = 0) => {
    const totalSteps = 100;
    const interval = setInterval(() => {
      step += 1;
      setProgress(step);
      if (step >= totalSteps) {
        clearInterval(interval);
      }
    }, 300);
  };

  return (
    <div className="min-h-screen flex items-center justify-center bg-gradient-to-r from-yellow-700 to-red-900">
      <div className="w-full max-w-lg bg-white p-10 rounded-lg shadow-lg">
        <Header />
        <RestoreProgress progress={progress} />
      </div>
    </div>
  );
}
